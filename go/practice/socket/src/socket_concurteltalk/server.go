package main

import (
	"fmt"
	"net"
)

var mymap map[string]net.Conn = make(map[string]net.Conn)

func Recev(conn net.Conn) {
	defer fmt.Println(conn.RemoteAddr().String() + "quit")
	defer conn.Close()
	defer delete(mymap, conn.RemoteAddr().String())
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
		fmt.Println("received data", string(buffer[:n]))
	}
}

func main() {
	listener, err := net.Listen("tcp", "127.0.0.1:8848")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer listener.Close()

	go func() {
		for {
			var input string
			fmt.Scanf("%s", &input)
			var user string
			fmt.Scanf("%s", &user)
			myconn := mymap[user]
			fmt.Println("send to:", myconn.RemoteAddr().String(), input)
			n, err := myconn.Write([]byte(input))
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("send succeed", n, input)
		}
	}()

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println(err)
			return
		}
		mymap[conn.RemoteAddr().String()] = conn
		fmt.Println("new conn from:", conn.RemoteAddr().String())
		for k, v := range mymap {
			fmt.Println(k, v)
		}
		go Recev(conn)
	}

}
