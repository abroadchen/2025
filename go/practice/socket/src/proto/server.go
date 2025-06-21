package main

import (
	"errors"
	"net"
	"net/http"
	"net/rpc"
	"socket/src/proto/message"
	"time"
)

type OrderService struct {
}

func (os *OrderService) GetOrderInfo(request message.OrderRequest, response *message.OrderInfo) error {
	orderMap := map[string]message.OrderInfo{
		"201907300001": message.OrderInfo{OrderId: "201907300001", OrderName: "衣服", OrderStatus: "已付款"},
	}
	current := time.Now().Unix()
	if request.TimeStamp > current {
		*response = message.OrderInfo{OrderId: "0", OrderName: "", OrderStatus: "订单信息异常"}
	} else {
		request := orderMap[request.OrderId]
		if request.OrderId != "" {
			*response = orderMap[request.OrderId]
		} else {
			return errors.New("server err")
		}
	}
	return nil
}

func main() {
	orderService := new(OrderService)
	rpc.Register(orderService)
	rpc.HandleHTTP()
	listener, err := net.Listen("tcp", ":1234")
	if err != nil {
		panic(err.Error())
	}
	http.Serve(listener, nil)
}
