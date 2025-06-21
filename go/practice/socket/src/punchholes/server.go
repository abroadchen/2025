package main

import (
	"log"
	"net"
	"time"
)

func main() {
	listenUdpZero, e := net.ListenUDP("udp", &net.UDPAddr{IP: net.IPv4zero, Port: 0})
	if e != nil {
		panic(e)
	}
	defer listenUdpZero.Close()
	log.Println("Listening on", listenUdpZero.LocalAddr().String())
	peers := make([]net.UDPAddr, 0, 2)
	data := make([]byte, 1024)
	for {
		i, addr, e := listenUdpZero.ReadFromUDP(data)
		if e != nil {
			log.Println("Error reading from udp connection:", e)
		}
		log.Println("<%s>%s\n", addr.String(), "bytes", data[:i])
		peers = append(peers, *addr)
		if len(peers) == 2 {
			log.Println("%s < - - > %s", peers[0].String(), peers[1].String())
			listenUdpZero.WriteToUDP([]byte(peers[1].String()), &peers[0])
			listenUdpZero.WriteToUDP([]byte(peers[1].String()), &peers[1])
			time.Sleep(time.Second * 8)
			log.Println("servers quit cannot ")
			return
		}
	}
}
