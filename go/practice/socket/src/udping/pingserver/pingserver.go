package main

import (
	"log"
	"net"
)

type PongServer struct {
	Addrs []*net.UDPAddr
}

func NewPongServer(addrs ...*net.UDPAddr) *PongServer {
	if len(addrs) == 0 {
		log.Fatalln("please input at least one UDP address")
	}
	return &PongServer{Addrs: addrs}
}

func (server *PongServer) ListenAndPong() {
	for i, addr := range server.Addrs {
		addr := addr
		go server.ListenAndPong(i, addr)
	}
}
