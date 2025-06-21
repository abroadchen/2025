package main

import (
	"fmt"
	"log"
	"net"
	"strconv"
	"strings"
	"time"
)

const HAND_SHAKE_MSG = ""

func main() {
	tag := "127.0.0.1"
	srcAddr := &net.UDPAddr{IP: net.IPv4zero, Port: 9901}
	dstAddr := &net.UDPAddr{IP: net.ParseIP(tag), Port: 9902}
	conn, err := net.DialUDP("udp", srcAddr, dstAddr)
	if err != nil {
		log.Panic(err)
	}
	defer conn.Close()
	if _, err := conn.Write([]byte(HAND_SHAKE_MSG + tag)); err != nil {
		log.Panic(err)
	}
	buf := make([]byte, 1024)
	i, addr, err := conn.ReadFromUDP(buf)
	if err != nil {
		log.Panic(err)
	}
	udpAddr := parseAddr(string(buf[:i]))
	fmt.Println("local:%s server:%s another:%s\n", srcAddr, addr, udpAddr.String())
	bidirectionHole(srcAddr, &udpAddr)
}

func bidirectionHole(srcAddr *net.UDPAddr, dstAddr *net.UDPAddr) {
	conn, err := net.DialUDP("udp", srcAddr, dstAddr)
	if err != nil {
		log.Panic(err)
	}
	defer conn.Close()
	if _, e := conn.Write([]byte(HAND_SHAKE_MSG)); e != nil {
		log.Println("Send handshake error:", e)
	}
	go func() {
		for {
			time.Sleep(10 * time.Second)
			if _, err := conn.Write([]byte("from[" + srcAddr.String())); err != nil {
				log.Println("Send handshake error:", err)
			}
		}
	}()
}

func parseAddr(addr string) net.UDPAddr {
	t := strings.Split(addr, ":")
	i, _ := strconv.Atoi(t[1])
	return net.UDPAddr{
		IP:   net.ParseIP(t[0]),
		Port: i,
	}
}
