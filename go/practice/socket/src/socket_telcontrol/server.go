package main

import (
	"fmt"
	"net"
	"os/exec"
)

func main() {
	listener, err := net.Listen("tcp", "127.0.0.1:8848")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer listener.Close()

	conn, err := listener.Accept()
	if err != nil {
		fmt.Println(err)
		return
	}
	defer conn.Close()

	for {
		buffer := make([]byte, 4096)
		n, err := conn.Read(buffer)
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println("server received data", string(buffer[:n]))
		cmd := exec.Command(string(buffer[:n]))
		out, err := cmd.CombinedOutput()
		if err != nil {
			fmt.Println(err)
		}
		conn.Write([]byte("ok" + string(out)))
	}
}
