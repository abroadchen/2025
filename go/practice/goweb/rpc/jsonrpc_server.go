/*
Package rpc

	@author: June
	@since: 2025/7/18
	@desc:
*/
package rpc

import (
	"errors"
	"fmt"
	"log"
	"net"
	"net/rpc"
	"net/rpc/jsonrpc"
	"os"
)

type Arith struct{}

type ArithRequest struct {
	A, B int
}
type ArithResponse struct {
	Pro int //乘积
	Quo int //商
	Rem int //余数
}

func (this *Arith) Multiply(req *ArithRequest, res *ArithResponse) error {
	res.Pro = req.A * req.B
	return nil
}

func (this *Arith) Divide(req *ArithRequest, res *ArithResponse) error {
	if req.B == 0 {
		return errors.New("divide by zero")
	}
	res.Quo = req.A / req.B
	res.Rem = req.A % req.B
	return nil
}

func main() {
	rpc.Register(new(Arith))

	lis, err := net.Listen("tcp", "127.0.0.1:8080")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Fprintf(os.Stdout, "server listening at %v\n", lis.Addr())

	for {
		conn, err := lis.Accept()
		if err != nil {
			continue
		}

		go func(conn net.Conn) {
			fmt.Fprintln(os.Stdout, "new connection")
			jsonrpc.ServeConn(conn)
		}(conn)
	}
}
