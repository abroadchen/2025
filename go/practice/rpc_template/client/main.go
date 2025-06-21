package main

import (
	"context"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"log"
	"rpc_template/proto/user"
)

type (
	GetUserReq struct {
		Id string `json:"id"`
	}
	GetUserResp struct {
		Id    string
		Name  string
		Phone string
	}
)

func main() {
	//client, err := rpc.Dial("tcp", "localhost:1234")
	//if err != nil {
	//	log.Fatal("dialing:", err)
	//}
	//defer client.Close()
	//var (
	//	req  = GetUserReq{Id: "1"}
	//	resp GetUserResp
	//)
	//err = client.Call("UserServer.GetUser", req, &resp)
	//if err != nil {
	//	log.Fatal("call:", err)
	//	return
	//}
	//log.Println(resp)

	client, err := grpc.NewClient("127.0.0.1:1234", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatal("dial err:", err)
	}
	defer client.Close()
	c := user.NewUserClient(client)
	res, err := c.GetUser(context.Background(), &user.GetUserReq{Id: "1"})
	if err != nil {
		log.Fatal("get err:", err)
	}
	log.Println(res)
}
