package main

import (
	"fmt"
	"net"
)

func main() {

	conn, err := net.Dial("tcp", "127.0.0.1:8848")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer conn.Close()

	go func() {
		for {
			buffer := make([]byte, 4096)
			n, err := conn.Read(buffer)
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("client received", string(buffer[:n]))
		}
	}()
	for {
		var input string
		fmt.Scanf("%s", &input)
		n, err := conn.Write([]byte(input))
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println("send succeed", n, input)
	}
}
