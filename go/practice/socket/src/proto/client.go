package main

import (
	"fmt"
	"net/rpc"
	"socket/src/proto/message"
	"time"
)

func main() {
	client, err := rpc.DialHTTP("tcp", "127.0.0.1:8080")
	if err != nil {
		panic(err.Error())
	}
	timeStamp := time.Now().Unix()
	request := message.OrderRequest{OrderId: "201907300001", TimeStamp: timeStamp}
	var response *message.OrderInfo
	err = client.Call("OrderService.GetOrderInfo", request, &response)
	if err != nil {
		panic(err.Error())
	}
	fmt.Println(*response)
}
