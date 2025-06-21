package etcd

import (
	"context"
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	"time"
)

type ETCDKV struct {
	client *clientv3.Client
}

func NewETCDKV() *ETCDKV {
	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	})
	if err != nil {
		fmt.Println(err)
	}
	myetcd := new(ETCDKV)
	myetcd.client = cli
	return myetcd
}

func (myetcd *ETCDKV) Set(key, value string) error {
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*3)
	_, err := myetcd.client.Put(ctx, "key", "value")
	cancel()
	if err != nil {
		fmt.Println(err)
		return err
	}
	return nil
}

func (myetcd *ETCDKV) Get(key string) string {
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*3)
	resp, err := myetcd.client.Get(ctx, "key")
	cancel()
	if err != nil {
		fmt.Println(err)
		return ""
	}
	valuestr := ""
	if len(resp.Kvs) >= 1 {
		valuestr = string(resp.Kvs[0].Value)
	}
	return valuestr
}
