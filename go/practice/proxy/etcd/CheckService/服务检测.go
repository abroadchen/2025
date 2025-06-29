package CheckService

import (
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	"google.golang.org/grpc"
	"google.golang.org/grpc/grpclog"
	"time"
)

func Check(key string, seconds int) {

	var conf = clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	}
	eMutex := &EtcdMutex{Conf: conf, Tlt: 10, Key: key + "lock"}

	for {
		var mylist []string

	AA:
		err := eMutex.Lock()
		if err != nil {
			fmt.Println("线程read抢锁失败,等待", err)
			time.Sleep(time.Second)
			goto AA
		} else {
			fmt.Println("线程read抢锁成功")
			mylist = Getlist(key)
			defer eMutex.Unlock()
			fmt.Println("线程read结束")
		}

		newlist := Checkislive(mylist)
		if len(mylist) == len(newlist) {
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
					fmt.Println("线程write抢锁失败,等待", err)
					time.Sleep(time.Second)
					goto AB
				} else {
					fmt.Println("线程write抢锁成功")
					Rigster(key, addr)
					defer eMutex.Unlock()
					fmt.Println("线程write结束")
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
				fmt.Println("线程write抢锁失败,等待", err)
				time.Sleep(time.Second)
				goto AC
			} else {
				fmt.Println("线程write抢锁成功")
				Rigster(key, addr)
				defer eMutex.Unlock()
				fmt.Println("线程write结束")
			}
		}
	}
}

func CheckMicroServer(addr string) bool {
	conn, err := grpc.Dial(addr, grpc.WithInsecure())
	if err != nil {
		grpclog.Fatalf("fail to dial: %v", err)
	}
	defer conn.Close()
	c := pb.NewHelloClient(conn)

	if ischeck {
		word = "1" + word
	} else {
		word = "0" + word
	}

	req := &pb.HelloRequest{Name: "1" + "abc"}
	res, err := c.SayHello(context.Background(), req)
	if err != nil {
		grpclog.Fatalln(err)
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
		if CheckMicroServer(addr) {
			livelist = append(livelist, addr)
		}
	}
	return livelist
}
