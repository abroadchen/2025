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
	fmt.Println(addr, "create server addr")
	conn, err := net.ListenUDP("udp", addr)
	if err != nil {
		log.Fatal(err)
	}
	defer conn.Close()
	fmt.Println("create server")
	for {
		//fmt.Println(conn.RemoteAddr().String() + "add")
		handle(conn)
	}
}

func handle(conn *net.UDPConn) {
	var myaddr *net.UDPAddr

	go func() {
		var input string
		fmt.Scanf("%s", &input)
		conn.WriteTo([]byte(input), myaddr)
	}()
	for {
		buffer := make([]byte, 4096)
		n, addr, err := conn.ReadFromUDP(buffer[:])
		myaddr = addr
		fmt.Println(myaddr.String())
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println("received data", string(buffer[:n]))
	}

}
