package main

import (
	"fmt"
	"log"
	"net"
	"sync"
)

var mymap sync.Map

func main() {

	addr, err := net.ResolveUDPAddr("udp", "127.0.0.1:8080")
	if err != nil {
		log.Fatal(err)
	}
	conn, err := net.ListenUDP("udp", addr)
	if err != nil {
		log.Fatal(err)
	}

	Handle(conn)
}

func Handle(conn *net.UDPConn) {

	for {
		buffer := make([]byte, 4096)
		n, addr, err := conn.ReadFromUDP(buffer[:])
		mymap.Store(addr.String(), addr)
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println("received data", addr.String(), string(buffer[:n]))
		mymap.Range(func(key, value interface{}) bool {
			conn.WriteTo([]byte(addr.String()+":"+string(buffer[:n])), value.(*net.UDPAddr))
			return true
		})
	}
}
