package main

import (
	"fmt"
	"log"
	"net"
	"net/rpc"
	"net/rpc/jsonrpc"
)

type HelloServiceClient struct {
	*rpc.Client
}

var _ HelloServiceInterface = (*HelloServiceClient)(nil)

func DialHelloService(network string, address string) (*HelloServiceClient, error) {
	c, err := rpc.Dial(network, address)
	if err != nil {
		return nil, err
	}
	return &HelloServiceClient{c}, nil
}

func (p *HelloServiceClient) Hello(request string, reply *string) error {
	return p.Client.Call(HelloServiceName+".Hello", request, reply)
}

func main() {
	//client, err := DialHelloService("tcp", "127.0.0.1:1234")
	//if err != nil {
	//	log.Fatal("dialing:", err)
	//}
	//var reply string
	//err = client.Hello("hello", &reply)
	//if err != nil {
	//	log.Fatal("Call:", err)
	//}

	conn, err := net.Dial("tcp", "localhost:1234")
	if err != nil {
		log.Fatal("dialing:", err)
	}
	client := rpc.NewClientWithCodec(jsonrpc.NewClientCodec(conn))
	var reply string
	err = client.Call(HelloServiceName+".Hello", "hello", &reply)
	if err != nil {
		log.Fatal("Call:", err)
	}
	fmt.Println(reply)
}
