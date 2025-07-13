package etcd

import (
	"context"
	"errors"
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	"time"
)

type EtcdMutex struct {
	Tlt     int64
	Conf    clientv3.Config
	Key     string
	cancel  context.CancelFunc
	lease   clientv3.Lease
	leaseID clientv3.LeaseID
	txn     clientv3.Txn
}

func (em *EtcdMutex) init() error {
	var err error
	var ctx context.Context
	client, err := clientv3.New(em.Conf)
	if err != nil {
		return err
	}
	em.txn = clientv3.NewKV(client).Txn(context.TODO())
	em.lease = clientv3.NewLease(client)
	leaseResp, err := em.lease.Grant(context.TODO(), em.Tlt)
	if err != nil {
		return err
	}
	ctx, em.cancel = context.WithCancel(context.TODO())
	em.leaseID = leaseResp.ID
	_, err = em.lease.KeepAlive(ctx, em.leaseID)
	return err
}

func (em *EtcdMutex) Lock() error {
	err := em.init()
	if err != nil {
		return err
	}
	em.txn.If(clientv3.Compare(clientv3.CreateRevision(em.Key), "=", 0)).Then(
		clientv3.OpPut(em.Key, "", clientv3.WithLease(em.leaseID))).Else()
	txnresp, err := em.txn.Commit()
	if err != nil {
		return err
	}
	if !txnresp.Succeeded {
		return errors.New("lock failed")
	}
	return nil
}

func (em *EtcdMutex) Unlock() {
	em.cancel()
	em.lease.Revoke(context.TODO(), em.leaseID)
	fmt.Println("unlock")
}

func main() {
	var conf = clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	}
	eMutex1 := &EtcdMutex{Conf: conf, Tlt: 10, Key: "lock"}
	eMutex2 := &EtcdMutex{Conf: conf, Tlt: 10, Key: "lock"}
	go func() {
	AA:
		err := eMutex1.Lock()
		if err != nil {
			fmt.Println("thread1 failed to lock")
			fmt.Println(err)
		} else {
			time.Sleep(time.Second)
			goto AA
		}
		fmt.Println("thread1 locked success")
		time.Sleep(time.Second * 10)
		defer eMutex1.Unlock()
	}()
	go func() {
	AB:
		err := eMutex2.Lock()
		if err != nil {
			fmt.Println("thread2 failed to lock")
			fmt.Println(err)
		} else {
			time.Sleep(time.Second)
			goto AB
		}
		fmt.Println("thread2 locked success")
		time.Sleep(time.Second * 10)
		defer eMutex2.Unlock()
	}()
	time.Sleep(time.Second * 30)
}
