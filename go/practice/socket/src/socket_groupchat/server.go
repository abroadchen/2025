package main

import (
	"fmt"
	"net"
	"sync"
)

var mymap sync.Map

func RecevALL(conn net.Conn) {
	defer fmt.Println(conn.RemoteAddr().String() + "quit")
	defer conn.Close()
	defer mymap.Delete(conn.RemoteAddr().String())
	var input string = "start"
	n, err := conn.Write([]byte(input))
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println("send succeed", n, input)
	for {
		buffer := make([]byte, 4096)
		n, err := conn.Read(buffer)
		if err != nil {
			fmt.Println(err)
			return
		}

		sendstr := conn.RemoteAddr().String() + " say: " + string(buffer[:n])
		fmt.Println(sendstr)
		mymap.Range(func(k, v interface{}) bool {
			n, err := v.(net.Conn).Write([]byte(sendstr))
			if err != nil {
				fmt.Println(err)
				return false
			}
			fmt.Println("send succeed", n, input)
			return true
		})
	}
}

func main() {

	listener, err := net.Listen("tcp", "127.0.0.1:8848")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer listener.Close()

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println(err)
			return
		}
		//mymap[conn.RemoteAddr().String()] = conn
		mymap.Store(conn.RemoteAddr().String(), conn)
		fmt.Println("new conn from:", conn.RemoteAddr().String())
		mymap.Range(func(key, value interface{}) bool {
			fmt.Println(key, value)
			return true
		})
		go RecevALL(conn)
	}
}
