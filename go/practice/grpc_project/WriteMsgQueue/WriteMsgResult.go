package WriteMsgQueue

import (
	"fmt"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/grpclog"
	"strings"
)

var isstart = 0

const (
	Address = "localhost:50062"
)

type helloService struct{}

var HelloService = helloService{}

func (h helloService) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	resp := new(pb.HelloResponse)
	myp := NewMyproduct()
	myp.Pub("ToResult", in.Name)
	if isstart == 0 {
		Send("127.0.0.1:50042", "start")
		isstart = 1
	}
	resp.Message = fmt.Sprintf("进入队列", mystr)
	return resp, nil
}

func main() {
	conn, err := grpc.NewClient(Address, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Println(err)
	}
	defer conn.Close()
	c := pb.NewHelloClient(conn)

	req := &pb.HelloRequest{Name: "start"}
	res, err := c.SayHello(context.Background(), req)

	if err != nil {
		grpclog.Fatalf("could not greet: %v", err)
	}
	fmt.Println(res.Message)
}
