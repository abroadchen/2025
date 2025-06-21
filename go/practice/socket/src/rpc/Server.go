package main

import (
	"math"
	"net"
	"net/http"
	"net/rpc"
)

type MathUtil struct {
}

func (mu *MathUtil) CalculateCircleArea(req float32, resp *float32) error {
	*resp = math.Pi * req * req
	return nil
}

type AddParam struct {
	Arg1, Arg2 float32
}

func (mu *MathUtil) Add(param AddParam, resp *float32) error {
	*resp = param.Arg1 + param.Arg2
	return nil
}

func main() {
	mathUtil := new(MathUtil)
	err := rpc.Register(mathUtil)
	if err != nil {
		panic(err.Error())
	}
	rpc.HandleHTTP()
	listener, err := net.Listen("tcp", ":1234")
	if err != nil {
		panic(err.Error())
	}
	go http.Serve(listener, nil)
}
