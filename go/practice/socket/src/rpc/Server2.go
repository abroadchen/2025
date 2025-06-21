package main

import (
	"log"
	"net"
	"net/rpc"
)

type HelloService struct {
}

func (this *HelloService) Hello(request string, reply *string) error {
	*reply = "Hello " + request
	return nil
}

func main() {
	rpc.RegisterName("HelloService", new(HelloService))
	listener, err := net.Listen("tcp", ":1234")
	if err != nil {
		log.Fatal("listen error:", err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Fatal("accept error:", err)
		}
		rpc.ServeConn(conn)
	}
}
