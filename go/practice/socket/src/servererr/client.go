package main

import (
	"fmt"
	"net"
	"time"
)

func main() {
	conn, err := net.DialTimeout("tcp", "localhost:8080", time.Second)
	if err != nil {
		fmt.Println(err)
		return
	}
	err = conn.SetDeadline(time.Now().Add(time.Second))
	if err != nil {
		fmt.Println(err)
		return
	}
	start := time.Now()
	fmt.Println("Connected")
	defer func() {
		fmt.Println("Disconnected", time.Now().Sub(start))
	}()
	expectedToRead := 2
	data := make([]byte, 2)
	read, err := conn.Read(data)
	if err != nil {
		fmt.Println(err)
		return
	}
	if read != expectedToRead {
		fmt.Println("Expected to read", expectedToRead, "but got", read)
		return
	}
}
