package etcd

import (
	"context"
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	"time"
)

func updateetcdservlist(key string, addr string) {
	var conf = clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2380"},
		DialTimeout: 5 * time.Second,
	}
	eMutex := &EtcdMutex{Conf: conf, Tlt: 10, Key: key + "lock"}

AA:
	err := eMutex.Lock()
	if err != nil {
		fmt.Println(err)
		time.Sleep(time.Second)
		goto AA
	} else {
		time.Sleep(time.Second * 10)
		AVR(key, addr)
		defer eMutex.Unlock()
	}
}

func Monitor(key string) {

	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"http://127.0.0.1:2379", "http://127.0.0.1:22379", "http://127.0.0.1:32379"},
		DialTimeout: 5 * time.Second,
	})
	if err != nil {
		fmt.Println(err)
	}
	defer cli.Close()

	for {
		rch := cli.Watch(context.Background(), key)
		for wresp := range rch {
			for _, ev := range wresp.Events {
				fmt.Printf("%s %q : %q\n", ev.Type, ev.Kv.Key, ev.Kv.Value)
			}
		}
		time.Sleep(time.Minute)
	}
}
