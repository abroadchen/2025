package etcd

import (
	"context"
	"fmt"
	pb "github.com/jergoo/go-grpc-expample/proto/hello"
	clientv3 "go.etcd.io/etcd/client/v3"
	"google.golang.org/grpc"
	"google.golang.org/grpc/grpclog"
	"strings"
	"time"
)

func Getlist(key string) []string {
	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"http://127.0.0.1:2379", "http://127.0.0.1:22379", "http://127.0.0.1:32379"},
		DialTimeout: 5 * time.Second,
	})
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("连接成功")
	defer cli.Close()
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*3)
	resp, err := cli.Get(ctx, key)
	cancel()
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	mylist := []string{}
	mystr := ""
	for _, kv := range resp.Kvs {
		if string(kv.Key) == key {
			mystr = string(kv.Value)
		}
	}
	mylist = strings.Split(mystr, "#$#")
	return mylist
}

func Rigster(key, value string) bool {
	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"http://127.0.0.1:2379", "http://127.0.0.1:22379", "http://127.0.0.1:32379"},
		DialTimeout: 5 * time.Second,
	})
	if err != nil {
		fmt.Println(err)
		return false
	}
	defer cli.Close()
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*3)
	_, err = cli.Put(ctx, key, value)
	cancel()
	if err != nil {
		fmt.Println(err)
		return false
	}
	return true
}

func CheckMircoServer(addr string) bool {
	conn, err := grpc.Dial(addr, grpc.WithInsecure())
	if err != nil {
		grpclog.Fatalf("fail to dial: %v", err)
	}
	defer conn.Close()
	c := pb.NewHelloClient(conn)
	req := &pb.HelloRequest{Name: "1" + "abc"}
	res, err := c.SayHello(context.Background(), req)

	if err != nil {
		grpclog.Fatalf("SayHello err: %v", err)
	}
	if res.Message == "live" {
		return true
	} else {
		return false
	}
}

func Checkislive(addrs []string) []string {
	livelist := []string{}
	for _, addr := range addrs {
		if CheckMircoServer(addr) {
			livelist = append(livelist, addr)
		}
	}
	return livelist
}

func Check(key string, seconds int) {

	var conf = clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2380"},
		DialTimeout: 5 * time.Second,
	}
	eMutex := &EtcdMutex{Conf: conf, Tlt: 10, Key: key + "lock"}

	for {
		var mylist []string
	AA:
		err := eMutex.Lock()
		if err != nil {
			fmt.Println(err)
			time.Sleep(time.Second)
			goto AA
		} else {
			time.Sleep(time.Second * 10)
			mylist = Getlist(key)
			defer eMutex.Unlock()
		}

		newlist := Checkislive(mylist)

		if len(newlist) == len(mylist) {
			var isok bool = true
			for i := 0; i < len(mylist); i++ {
				if mylist[i] != newlist[i] {
					isok = false
					break
				}
			}
			if isok == false {
				mystr := ""
				for _, mylistdata := range mylist {
					mystr += mylistdata
					mystr += "#$#"
				}

			AB:
				err := eMutex.Lock()
				if err != nil {
					fmt.Println(err)
					time.Sleep(time.Second)
					goto AB
				} else {
					time.Sleep(time.Second * 10)
					Rigster(key, mystr)
					defer eMutex.Unlock()
				}

			}
		} else {
			mystr := ""
			for _, mylistdata := range mylist {
				mystr += mylistdata
				mystr += "#$#"
			}

		AC:
			err := eMutex.Lock()
			if err != nil {
				fmt.Println(err)
				time.Sleep(time.Second)
				goto AC
			} else {
				time.Sleep(time.Second * 10)
				Rigster(key, mystr)
				defer eMutex.Unlock()
			}

		}

		time.Sleep(time.Duration(seconds) * time.Second)
	}
}

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
