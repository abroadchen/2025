package main

import (
	"context"
	"fmt"
	"net"
	"socket/src/proto/message"
	"time"
)

func main() {
	conn, err := net.Dial("tcp", grpc.WithInsecure())
	if err != nil {
		panic(err.Error())
	}
	defer conn.Close()
	orderServiceClient := message.NewOrderServiceClient(conn)
	orderRequest := &message.OrderRequest{OrderId: "", TimeStamp: time.Now().Unix()}
	orderInfo, err := orderServiceClient.GetOrderInfo(context.Background(), orderRequest)
	if err != nil {
		fmt.Println(orderInfo.GetOrderId())
		fmt.Println(orderInfo.GetOrderName())
		fmt.Println(orderInfo.GetOrderStatus())
	}
}
