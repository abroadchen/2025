package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strings"
)

func server(address string, exitChan chan int) {
	l, err := net.Listen("tcp", address)
	if err != nil {
		fmt.Println("Error listening:", err.Error())
		exitChan <- 1
	}
	fmt.Println("Listening on " + address)
	defer l.Close()
	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Println("Error accepting: ", err.Error())
			continue
		}
		go handleSession(conn, exitChan)
	}
}

func handleSession(conn net.Conn, exitChan chan int) {
	fmt.Println("Session started")
	reader := bufio.NewReader(conn)
	for {
		str, err := reader.ReadString('\n')
		if err != nil {
			str = strings.TrimSpace(str)
			if !processTelnetCommand(str, exitChan) {
				conn.Close()
				break
			}
		} else {
			fmt.Println("Session closed")
			conn.Close()
			break
		}
	}
}

func processTelnetCommand(str string, exitChan chan int) bool {
	if strings.HasPrefix(str, "@close") {
		fmt.Println("Session closed")
		return false
	} else if strings.HasPrefix(str, "@shutdown") {
		fmt.Println("Session shutdown")
		exitChan <- 0
		return false
	}
	fmt.Println(str)
	return true
}

func main() {
	exitChan := make(chan int)
	go server("localhost", exitChan)
	code := <-exitChan
	os.Exit(code)
}
