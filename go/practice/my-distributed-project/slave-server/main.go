package main

import (
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	"net"
	"slave-server/log"
	"slave-server/myerror"
	"slave-server/network/threadrun"
	"slave-server/network/threadsafenetwork"
	"slave-server/nsq"
	"slave-server/staticdata"
	"slave-server/test"
	"slave-server/thread/mem"
	"strconv"
	"time"
)

func init() {
	go func() {
		var conf = clientv3.Config{
			Endpoints:   []string{"127.0.0.1:2379"},
			DialTimeout: 5 * time.Second,
		}
		eMutex1 := &EtcdMutex{Conf: conf, Tlt: 10, Key: "lock"}
	AA:
		err := eMutex1.Lock()
		if err != nil {
			time.Sleep(time.Second)
			goto AA
		} else {
			fmt.Println("thread1 locked success")
			numstr := staticdata.DataETCDServer.Get("Clientnum")
			if numstr == "" {
				staticdata.DataETCDServer.Set("Clientnum", "1")
			} else {
				num, err := strconv.Atoi(numstr)
				if err != nil {
					staticdata.DataETCDServer.Set("Clientnum", "1")
				} else {
					staticdata.DataETCDServer.Set("Clientnum", strconv.Itoa(num+1))
				}
			}
			myipstr := test.Getip()
			myallipstr := staticdata.DataETCDServer.Get("Clientlist")
			if myallipstr == "" {
				staticdata.DataETCDServer.Set("Clientlist", "1")
			} else {
				myallipstr += " # "
				myallipstr += myipstr
				staticdata.DataETCDServer.Set("Clientlist", myallipstr)
			}
			time.Sleep(time.Second * 10)
			defer eMutex1.Unlock()
		}
	}()
}

func main() {

	if staticdata.IsMEM {
		for i := 0; i < int(staticdata.ThreadNum); i++ {
			go mem.EmailChanThread()
		}
		go mem.Monitor()
	}

	go func() {
		for {
			staticdata.Mylog = log.Newlogfile()
			staticdata.Mylog.Loger.Println("today's log begin")
			time.Sleep(time.Hour * 24)
		}
	}()

	if staticdata.IsNSQ {
		nsq.NSQThread()
	} else {

		server_listener, err := net.Listen("tcp", ":8080")
		if err != nil {
			myerror.CheckError(err)
		}
		defer server_listener.Close()
		for {
			new_conn, err := server_listener.Accept()
			if err != nil {
				myerror.CheckError(err)
			}
			go threadrun.MsgHandle(new_conn)
			if staticdata.IsMEM {
				go mem.SaveEmailChan(*threadsafenetwork.NewReturnEmail(new_conn))
			}
		}
	}
}
