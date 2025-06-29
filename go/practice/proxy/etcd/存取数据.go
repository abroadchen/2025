package etcd

import (
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	"time"
)

func AVR(key string, addr string) {
	mylist := Getlist(key)
	if len(mylist) == 0 {
		fmt.Println(Rigster(key, addr))
	} else {
		mystr := ""
		for _, mylistdata := range mylist {
			mystr += mylistdata
			mystr += "#$#"
		}
		mystr += addr
		Rigster(key, addr)
	}
}

func Getlist(key string) []string {
	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379", "127.0.0.1:2379", "127.0.0.1:2379", "127.0.0.1:2379"},
		DialTimeout: time.Second * 5,
	})
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("连接成功")
	defer cli.Close()
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	resp, err := cli.Get(ctx, key)
	cancel()
	if err != nil {
		fmt.Println("get", err)
		return []string{}
	}
}
