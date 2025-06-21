package main

import (
	"fmt"
	"master-server/data-server/store/savetxt"
	"master-server/datastruct/queue"
	error2 "master-server/error"
	"master-server/log"
	"master-server/network"
	"master-server/staticdata"
	"master-server/thread"
	"master-server/thread/mem"
	"net"
	"os"
	"sync"
	"time"
)

var ThreadNum int64 = 0

func main1() {
	//q1 := queue.Queue{make(chan string, 1000)}
	//q2 := queue.Queue{make(chan string, 1000)}
	//mystack := Stack.Stack{q1, q2}
	//mystack.Push("a")
	//mystack.Push("b")
	//mystack.Push("c")
	//fmt.Println(mystack.Pop())
	//fmt.Println(mystack.Pop())
	//fmt.Println(mystack.Pop())

	var sf = savetxt.NewSafeFile("savemail.txt")

	go thread.CheckThreadNum()

	url := ""
	//myqueue := list.New()
	//myqueue.PushBack(url)
	myQueue := queue.Queue{make(chan string, 1000)}
	myQueue.Enqueue(url)
	var wg sync.WaitGroup
AAA:
	for len(myQueue.Items) != 0 {
		time.Sleep(time.Second)
		myurl := myQueue.Dequeue()
		//go Getmailmap(myurl.Value.(string))
		wg.Add(1)
		if staticdata.ThreadNum < staticdata.MAXTHREADNUM {
			go thread.GetMailThread(sf, myurl, &wg, &myQueue)
			go thread.GetURLThread(myurl, &myQueue, sf, &wg)
		} else {
			thread.GetMailThread(sf, myurl, &wg, &myQueue)
			thread.GetURLThread(myurl, &myQueue, sf, &wg)
		}
	}
	time.Sleep(time.Second)
	goto AAA
	wg.Wait()
	fmt.Println("done")
}

func main2() {
	go mem.Monitor()

	go func() {
		for {
			staticdata.Mylog = log.Newlogfile()
			staticdata.Mylog.Loger.Println("today's log start")
			time.Sleep(time.Hour * 24)
		}
	}()
	err := network.TestHTTP()
	if err != nil {
		staticdata.Mylog.Loger.Println("network problems quit")
		os.Exit(1)
	}
	url := ""
	go mem.MakeURLThread(url)
	for i := 0; i < int(staticdata.ThreadNum); i++ {
		go mem.EmailChanThread()
	}
	mem.SaveEmailChan("mail.txt")
}

func GetSlaveServers() []net.Conn {
	tcpaddr, err := net.ResolveTCPAddr("tcp4", "127.0.0.1:8848")
	if err != nil {
		error2.CheckError(err)
	}
	conn, err := net.DialTCP("tcp", nil, tcpaddr)
	if err != nil {
		error2.CheckError(err)
	}
	tcpaddr1, err := net.ResolveTCPAddr("tcp4", "127.0.0.1:8849")
	if err != nil {
		error2.CheckError(err)
	}
	conn1, err := net.DialTCP("tcp", nil, tcpaddr1)
	if err != nil {
		error2.CheckError(err)
	}
	tcpaddr2, err := net.ResolveTCPAddr("tcp4", "127.0.0.1:8850")
	if err != nil {
		error2.CheckError(err)
	}
	conn2, err := net.DialTCP("tcp", nil, tcpaddr2)
	if err != nil {
		error2.CheckError(err)
	}
	conns := make([]net.Conn, 3)
	conns[0] = conn
	conns[1] = conn1
	conns[2] = conn2
	return conns
}

func main() {
	go func() {
		for {
			staticdata.Mylog = log.Newlogfile()
			staticdata.Mylog.Loger.Println("today's log begin")
			time.Sleep(time.Hour * 24)
		}
	}()

	if staticdata.IsNSQ {
		url := ""
		thread.MakeURLforNSQ(url)
	} else {
		var sf = savetxt.NewSafeFile("savemail.txt")
		conns := GetSlaveServers()
		for _, conn := range conns {
			go thread.ServerMsgHandler(conn, sf)
		}
		url := ""
		go thread.MakeURLThread(url)
		thread.LoadBalanceURLChan(conns)
	}

}
