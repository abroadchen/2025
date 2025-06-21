package main

import (
	"fmt"
	"net"
	"os"
)

func recvFile(conn net.Conn, fileName string) {
	pathdir := ""
	f, err := os.Create(pathdir + "/" + fileName)
	if err != nil {
		fmt.Println("os.Create err:", err)
		return
	}
	defer f.Close()

	buf := make([]byte, 40960000)
	for {
		n, _ := conn.Read(buf)
		if n == 0 {
			fmt.Println("receiving file finished")
			return
		}
		f.Write(buf[:n])
	}
}

func main() {

	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println("net.Listen err:", err)
		return
	}
	defer listener.Close()

	conn, err := listener.Accept()
	if err != nil {
		fmt.Println("listener.Accept err:", err)
		return
	}
	defer conn.Close()

	buf := make([]byte, 4096)
	n, err := conn.Read(buf)
	if err != nil {
		fmt.Println("conn.Read err:", err)
		return
	}
	fileName := string(buf[:n])
	conn.Write([]byte("ok"))

	recvFile(conn, fileName)
}
