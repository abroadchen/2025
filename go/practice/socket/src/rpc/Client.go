package main

import (
	"fmt"
	"net/rpc"
)

func main() {
	client, err := rpc.DialHTTP("tcp", "127.0.0.1:1234")
	if err != nil {
		panic(err.Error())
	}
	var req float32
	req = 3
	var resp *float32
	err = client.Call("MathUtil.CalculateCircleArea", req, &resp)
	if err != nil {
		panic(err.Error())
	}
	fmt.Println(*resp)

	add := new(AddParam)
	add.Arg2 = 10
	add.Arg1 = 20
	err = client.Call("add", add, &resp)
	if err != nil {
		panic(err.Error())
	}
	fmt.Println(*resp)
}
