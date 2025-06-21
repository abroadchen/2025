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

	go func() {
		for {
			//mymap.Range(func(k, v interface{}) bool {
			//	fmt.Println(k, v)
			//	return true
			//})
			var input string
			fmt.Scanf("%s", &input)
			var towho string
			fmt.Scanf("%s", &towho)
			fmt.Println(input, towho)
			myaddr, isok := mymap.Load(towho)
			if !isok {
				fmt.Println("get fail", isok, myaddr)
				continue
			} else {
				if myaddr == nil {
					fmt.Println("addr cannot be nil", myaddr)
					continue
				}
				fmt.Println("get ok", isok, myaddr.(*net.UDPAddr).String())
				conn.WriteTo([]byte(input), myaddr.(*net.UDPAddr))
			}
		}
	}()
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
	}
}
