package main

import (
	"fmt"
	"log"
	"net"
	"strings"
	"time"
)

type Client struct {
	C    chan string
	Name string
	Addr string
}

var onlineMap map[string]Client
var message = make(chan string)

func WriteMsgToClient(cln Client, conn net.Conn) {
	for msg := range cln.C {
		conn.Write([]byte(msg + "\n"))
	}
}

func MakeMsg(cln Client, msg string) (buf string) {
	buf = "[" + cln.Addr + "]" + cln.Name + ": " + msg
	return
}

func Manager() {
	onlineMap = make(map[string]Client)
	for {
		msg := <-message
		for _, cln := range onlineMap {
			cln.C <- msg
		}
	}
}

func main() {
	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Fatal(err)
	}
	defer listener.Close()
	go Manager()

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Println(err)
			continue
		}
		go handleConn(conn)
	}
}

func handleConn(conn net.Conn) {
	defer conn.Close()
	hasData := make(chan bool)
	netAddr := conn.RemoteAddr().String()
	cln := Client{make(chan string), netAddr, netAddr}
	onlineMap[netAddr] = cln
	go WriteMsgToClient(cln, conn)
	message <- MakeMsg(cln, "login")
	isQuit := make(chan bool)
	go func() {
		buf := make([]byte, 4096)
		for {
			n, err := conn.Read(buf)
			if n == 0 {
				isQuit <- true
				fmt.Println("find client\n", cln.Name)
				return
			}
			if err != nil {
				fmt.Println(err)
				return
			}
			msg := string(buf[:n-1])
			if msg == "who" && len(msg) == 3 {
				conn.Write([]byte("online user list:\n"))
				for _, user := range onlineMap {
					userInfo := user.Addr + ":" + user.Name + "\n"
					conn.Write([]byte(userInfo))
				}
			} else if len(msg) >= 8 && msg[:6] == "rename" {
				newName := strings.Split(msg, "|")[1]
				cln.Name = newName
				onlineMap[netAddr] = cln
				conn.Write([]byte("rename successful\n"))
			} else {
				message <- MakeMsg(cln, msg)
			}
			hasData <- true
		}
	}()

	for {
		select {
		case <-isQuit:
			delete(onlineMap, cln.Addr)
			message <- MakeMsg(cln, "logout")
			return
		case <-hasData:
		case <-time.After(time.Second * 60):
			delete(onlineMap, cln.Addr)
			message <- MakeMsg(cln, "time out")
			return

		}
	}
}
