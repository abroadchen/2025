package SendMail_Server

import (
	"fmt"
	pb "github.com/jergoo/go-grpc-example/proto/hello"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/grpclog"
	"net"
)

const (
	Address = "localhost:50052"
)

type helloService struct{}

var HelloService = helloService{}

func NewSendEmail(to ...string) bool {
	m := gomail.NewMessage()
	m.SetHeader("From", "")
	m.SetHeader("To", to...)
	m.SetAddressHeader("Cc", "", "")
	m.SetHeader("Subject", "")
	m.SetBody("text/html", "")
	m.Attach(filepath)
	if err := d.DialAndSend(m); err != nil {
		fmt.Println(err)
		return false
	} else {
		fmt.Println("成功")
		return true
	}
}

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

func (h helloService) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	resp := new(pb.HelloResponse)
	isok := NewSendEmail(in.Name)
	if isok {
		Send("127.0.0.1:50062", in.Name+"$#$1")
		resp.Message = fmt.Sprintf("%s.发送成功", in.Name)
	} else {
		Send("127.0.0.1:50062", in.Name+"$#$0")
		resp.Message = fmt.Sprintf("%s.发送失败", in.Name)
	}
	return resp, nil
}

func main() {
	listen, err := net.Listen("tcp", Address)
	if err != nil {
		grpclog.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	pb.RegisterHelloServer(s, &HelloService)

	grpclog.Println("Starting gRPC server on " + Address)
	s.Serve(listen)
}
