package main

import (
	"fmt"
	"net"
	"time"
)

func main() {
	//conn, err := net.Dial("tcp", "127.0.0.1:8848")
	conn, err := net.DialTimeout("tcp", "", 3*time.Second)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer conn.Close()

	conn.Write([]byte("hello server"))
	buffer := make([]byte, 4096)
	n, err := conn.Read(buffer)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println("received data", string(buffer[:n]))
}
