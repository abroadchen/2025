package util

import (
	"bytes"
	"container/list"
	"encoding/binary"
	"fmt"
	"master-server/webPageGet/GetURL"
	"net"
	"slave-server/webPageGet/GetMail"
	"time"
)

func IntToBytes(n int) []byte {
	data := int64(n)
	bytebuf := bytes.NewBuffer([]byte{})
	binary.Write(bytebuf, binary.BigEndian, data)
	return bytebuf.Bytes()
}

func BytesToInt(b []byte) int {
	bytebuf := bytes.NewBuffer(b)
	var data int64
	binary.Read(bytebuf, binary.BigEndian, &data)
	return int(data)
}

// slave
func MsgHandle(conn net.Conn) {
	defer conn.Close()
	for {
		buf := make([]byte, 8)
		n, err := conn.Read(buf)
		if err != nil || n != 8 {
			fmt.Println("read err: ", conn)
			return
		}
		length := BytesToInt(buf)
		buf2 := make([]byte, length)
		n, err = conn.Read(buf2)
		if err != nil || n != length {
			fmt.Println("read err: ", conn)
			return
		}
		fmt.Println("receive: ", string(buf2))
		emaillist := GetMail.GetMail(string(buf2))
		for _, e := range emaillist {
			mystr := e
			mystrlen := len(mystr)
			mybytes := IntToBytes(mystrlen)
			conn.Write(mybytes)
			conn.Write([]byte(mystr))
		}
	}
}

// master
func ServerMsgHandler(conn net.Conn) {
	defer conn.Close()
	for {
		buf := make([]byte, 8)
		n, err := conn.Read(buf)
		if err != nil || n != 8 {
			fmt.Println("read err: ", conn)
			return
		}
		length := BytesToInt(buf)
		buf2 := make([]byte, length)
		n, err = conn.Read(buf2)
		if err != nil || n != length {
			fmt.Println("read err: ", conn)
			return
		}
		fmt.Println("receive: ", string(buf2))
	}
}

type CONN struct {
	conn      net.Conn
	cpu       int
	mem       int
	tasks     int
	livetasks int
	replytime int
}

func main() {
	//slave
	server_listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		panic(err)
	}
	defer server_listener.Close()
	for {
		new_conn, err := server_listener.Accept()
		if err != nil {
			panic(err)
		}
		go MsgHandle(new_conn)
	}

	//master
	tcpaddr, err := net.ResolveTCPAddr("tcp4", "127.0.0.1:8080")
	if err != nil {
		panic(err)
	}
	conn, err := net.DialTCP("tcp", nil, tcpaddr)
	if err != nil {
		panic(err)
	}
	go ServerMsgHandler(conn)

	conns := make([]net.Conn, 3)
	conns[0] = conn
	conns[1] = conn
	conns[2] = conn
	conns[3] = conn
	conns[4] = conn
	conns[5] = conn

	go func() {
		url := ""
		myqueue := list.New()
		myqueue.PushBack(url)
		i := 0
		for myqueue.Len() != 0 {
			myurl := myqueue.Front()
			mystr := myurl.Value.(string)
			mystrlen := len(mystr)
			mybytes := IntToBytes(mystrlen)
			conns[i%len(conns)].Write(mybytes)
			conns[i%len(conns)].Write([]byte(mystr))
			//randnum, _ := rand.Int()
			//conns[randnum%len(conns)].Write(mybytes)
			//conns[randnum%len(conns)].Write([]byte(mystr))
			myqueue.Remove(myurl)
			urllist := GetURL.GetURL(myurl.Value.(string))
			for _, url := range urllist {
				myqueue.PushBack(url)
				//mystr := url
				//mystrlen := len(mystr)
				//mybytes := IntToBytes(mystrlen)
				//conn.Write(mybytes)
				//conn.Write([]byte(mystr))
			}
			i++
		}
	}()
	//for i := 0; i < 10; i++ {
	//	mystr := "received" + strconv.Itoa(i)
	//	mystrlen := len(mystr)
	//	mybytes := IntToBytes(mystrlen)
	//	conn.Write(mybytes)
	//	conn.Write([]byte(mystr))
	//}
	time.Sleep(time.Second * 10)
}
