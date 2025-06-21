package main

import (
	"fmt"
	"log"
	"net"
	"net/http"
	"os"
	"sync/atomic"
)

func main() {
	go func() {
		log.Println(http.ListenAndServe("localhost:6060", nil))
	}()
	l, err := net.ListenTCP("tcp", &net.TCPAddr{IP: net.IPv4(127, 0, 0, 1), Port: 0})
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	var connections uint64
	for {
		conn, err := l.AcceptTCP()
		if err != nil && err.Error() != "use of closed network connection" {
			fmt.Println(err)
			continue
		}
		count := atomic.AddUint64(&connections, 1)
		data := make([]byte, 1)
		go func(c uint64) {
			defer conn.Close()
			fmt.Println("Accepted connection:", c)
			conn.Read(data)
		}(count)
	}
}
