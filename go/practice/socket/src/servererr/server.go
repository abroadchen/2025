package main

import (
	"fmt"
	"net"
	"os"
	"os/signal"
	"syscall"
	"time"
)

func main() {

	l, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println("Error listening:", err.Error())
		os.Exit(1)
	}
	go func() {
		for {
			conn, err := l.Accept()
			if err != nil {
				fmt.Println("Error accepting: ", err.Error())
				continue
			}
			go func(c net.Conn) {
				fmt.Println("Accepting connection:")
				time.Sleep(time.Second * 10)
				c.Write([]byte("ok"))
				fmt.Println("Connection closed")
				c.Close()
			}(conn)
		}
	}()
	sigs := make(chan os.Signal)
	signal.Notify(sigs, syscall.SIGINT, syscall.SIGTERM)
	<-sigs
}
