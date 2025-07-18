/*
Package rpc

	@author: June
	@since: 2025/7/18
	@desc:
*/
package rpc

import (
	"fmt"
	"net"
	"net/rpc"
)

func main() {
	rect := new(Rect)
	rpc.Register(rect)

	tcpAddr, err := net.ResolveTCPAddr("tcp", "127.0.0.1:8080")
	if err != nil {
		fmt.Println(err)
	}

	listener, err := net.ListenTCP("tcp", tcpAddr)
	if err != nil {
		fmt.Println(err)
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		rpc.ServeConn(conn)
	}
}
