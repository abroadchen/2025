package main

import (
	"fmt"
	"log"
	"net"
	"os/exec"
)

func main() {
	addr, err := net.ResolveUDPAddr("udp", "127.0.0.1:8080")
	if err != nil {
		log.Fatal(err)
	}

	conn, err := net.ListenUDP("udp", addr)
	if err != nil {
		log.Fatal(err)
	}
	handle(conn)
}

func handle(conn *net.UDPConn) {

	for {
		buffer := make([]byte, 4096)
		n, addr, err := conn.ReadFromUDP(buffer[:])
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println("received data", string(buffer[:n]))
		cmd := exec.Command(string(buffer[:n]))
		out, err := cmd.CombinedOutput()
		if err != nil {
			fmt.Println(err)
		}
		conn.WriteTo([]byte(out), addr)
	}
}
