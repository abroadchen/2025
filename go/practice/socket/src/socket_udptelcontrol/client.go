package main

import (
	"fmt"
	"log"
	"net"
)

func main() {

	addr, err := net.ResolveUDPAddr("udp", "127.0.0.1:8080")
	if err != nil {
		log.Fatal(err)
	}
	conn, err := net.DialUDP("udp", nil, addr)
	if err != nil {
		log.Fatal(err)
	}

	for {
		var input string
		fmt.Scanf("%s", &input)
		conn.Write([]byte(input))
		buffer := make([]byte, 4096*8)
		n, err := conn.Read(buffer)
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println("received data", string(buffer[:n]))
	}
}
