package main

import (
	"bufio"
	"fmt"
	"io"
	"net"
)

func process(conn net.Conn) {
	defer conn.Close()
	reader := bufio.NewReader(conn)
	//var buf [1024]byte
	for {
		//n, err := reader.Read(buf[:])
		msg, err := Decode(reader)
		if err == io.EOF {
			//break
			return
		}
		if err != nil {
			fmt.Println("decode error:", err)
			//break
			return
		}
		//recvStr := string(buf[:n])
		//fmt.Println("recvStr:", recvStr)
		fmt.Println("received client data", msg)
	}
}

func main() {
	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println("listen error:", err)
		return
	}
	defer listener.Close()
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("accept error:", err)
			continue
		}
		go process(conn)
	}
}
