package client

import (
	"google.golang.org/grpc"
	pb "google.golang.org/grpc/examples/helloworld/helloworld"
	"google.golang.org/grpc/grpclog"
)

const (
	Address = "localhost:50052"
)

func main() {
	conn, err := grpc.NewClient(Address, grpc.WithInsecure())
	if err != nil {
		grpclog.Fatalf("fail to dial: %v", err)
	}
	defer conn.Close()

	c := pb.NewHelloClient(conn)

	req := &pb.HelloRequest{Name: "gRPC"}
	res, err := c.SayHello(context.Background(), req)

	if err != nil {
		grpclog.Fatalf("SayHello err: %v", err)
	}
	grpclog.Println(res.Message)
}
