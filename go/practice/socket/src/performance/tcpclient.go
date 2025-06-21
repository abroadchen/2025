package main

import (
	"fmt"
	"net"
	"time"
)

func main() {
	var id int
	for i := 0; i < 100000; i++ {
		go connect(&id)
		time.Sleep(time.Millisecond)
	}
}

func connect(id *int) {
	conn, err := net.Dial("tcp", "127.0.0.1:8000")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer conn.Close()
	*id++
	fmt.Println("Connected:", *id)
	for {
		conn.Write([]byte("a"))
		time.Sleep(time.Minute)
	}
}
