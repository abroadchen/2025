package main

import (
	"context"
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	"time"
)

func main1() {
	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	})
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("connect to etcd success")
	defer cli.Close()

	ctx, cancel := context.WithTimeout(context.Background(), time.Second*3)
	_, err = cli.Put(ctx, "key", "value")
	cancel()
	if err != nil {
		fmt.Println(err)
		return
	}
	ctx, cancel = context.WithTimeout(context.Background(), time.Second*3)
	resp, err := cli.Get(ctx, "key")
	cancel()
	if err != nil {
		fmt.Println(err)
		return
	}
	for _, ev := range resp.Kvs {
		fmt.Println(string(ev.Key), string(ev.Value))
	}

	cli.Put(context.Background(), "key", "value")
	for {
		rch := cli.Watch(context.Background(), "key")
		for wresp := range rch {
			for _, ev := range wresp.Events {
				fmt.Println(string(ev.Kv.Key), string(ev.Kv.Value))
			}
		}
		time.Sleep(time.Second)
	}
}
