package main

import (
	"context"
	"errors"
	"google.golang.org/grpc"
	"log"
	"net"
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

type UserServer struct{}

//func (*UserServer) GetUser(req GetUserReq, resp *GetUserResp) error {
//	if u, ok := users[req.Id]; ok {
//		*resp = GetUserResp{
//			Id:    u.Id,
//			Name:  u.Name,
//			Phone: u.Phone,
//		}
//		return nil
//	}
//	return errors.New("user not found")
//}

func (*UserServer) GetUser(ctx context.Context, req *user.GetUserReq) (*user.GetUserResp, error) {
	if u, ok := users[req.Id]; ok {
		return &user.GetUserResp{
			Id:    u.Id,
			Name:  u.Name,
			Phone: u.Phone,
		}, nil
	}
	return nil, errors.New("user not found")
}

func main() {
	//userServer := new(UserServer)
	//rpc.Register(userServer)
	listener, err := net.Listen("tcp", ":1234")
	if err != nil {
		log.Fatal("listen error:", err)
	}
	log.Println("rpc server listening at port 1234")
	//for {
	//	conn, err := listener.Accept()
	//	if err != nil {
	//		log.Println("accept error:", err)
	//		continue
	//	}
	//	go rpc.ServeConn(conn)
	//}
	s := grpc.NewServer(grpc.ChainUnaryInterceptor(LogInterceptor, ErrorInterceptor))
	user.RegisterUserServer(s, new(UserServer))
	s.Serve(listener)
}
