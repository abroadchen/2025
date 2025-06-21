package main

import (
	"io"
	"net/http"
	"net/rpc"
	"net/rpc/jsonrpc"
)

const HelloServiceName = "HelloService"

type HelloServiceInterface = interface {
	Hello(request string, reply *string) error
}

func RegisterHelloService(srv HelloServiceInterface) error {
	return rpc.RegisterName(HelloServiceName, srv)
}

type HelloService2 struct {
}

func (this *HelloService2) Hello(request string, reply *string) error {
	*reply = "hello: " + request
	return nil
}

func main() {
	//RegisterHelloService(new(HelloService2))
	//rpc.RegisterName("HelloService", new(HelloService2))
	//listener, err := net.Listen("tcp", ":1234")
	//if err != nil {
	//	log.Fatal("listen error:", err)
	//}
	//for {
	//	conn, err := listener.Accept()
	//	if err != nil {
	//		log.Fatal("accept error:", err)
	//	}
	//	//go rpc.ServeConn(conn)
	//
	//	go rpc.ServeCodec(jsonrpc.NewServerCodec(conn))
	//}

	rpc.RegisterName("HelloService", new(HelloService2))
	http.HandleFunc("/jsonrpc", func(w http.ResponseWriter, r *http.Request) {
		var conn io.ReadWriteCloser = struct {
			io.Writer
			io.ReadCloser
		}{
			ReadCloser: r.Body,
			Writer:     w,
		}
		rpc.ServeRequest(jsonrpc.NewServerCodec(conn))
	})
	http.ListenAndServe("0.0.0.0:8888", nil)
}
