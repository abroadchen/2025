package controlclient

import (
	"bufio"
	"fmt"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/grpclog"
	"grpchello/proto"
	"os"
)

func Send(myAddress string, sendstr string) {
	conn, err := grpc.NewClient(myAddress, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Println(err)
	}
	defer conn.Close()
	c := pb.NewHelloClient(conn)

	req := &pb.HelloRequest{Name: sendstr}
	res, err := c.SayHello(context.Background(), req)

	if err != nil {
		grpclog.Fatalf("could not greet: %v", err)
	}
	fmt.Println(res.Message)
}

func main() {
	var serviceHost = "127.0.0.1:8001"

	conn, err := grpc.NewClient(serviceHost, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Println(err)
	}
	defer conn.Close()

	c := pb.NewHelloClient(conn)
	req := &pb.HelloRequest{Name: "start"}
	res, err := c.SayHello(context.Background(), req)
	//client := proto.NewHelloClient(conn)
	//rsp, err := client.Say(context.TODO(), &proto.SayRequest{
	//	Name: "BOSIMA",
	//})

	if err != nil {
		grpclog.Fatalf("could not greet: %v", err)
	}

	fmt.Println(res.Message)

	//fmt.Println("按回车键退出程序...")
	//in := bufio.NewReader(os.Stdin)
	//_, _, _ = in.ReadLine()
}
