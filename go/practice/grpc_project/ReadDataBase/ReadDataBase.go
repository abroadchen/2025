package ReadDataBase

import (
	"fmt"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/grpclog"
	"net"
)

const (
	Address = "localhost:50092"
)

type helloService struct{}

var HelloService = helloService{}

func (h helloService) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	resp := new(pb.HelloResponse)
	if in.Name == "start" {
		var mydb *MySQLclient = NewMySQLclient("127.0.0.1", "root", "123456")
		mymaillist := mydb.GetallEmail()
		mystr := ""
		for _, mail := range mymaillist {
			mystr += mail
			mystr += "$#$"
		}
		Send("127.0.0.1:50082", mystr)
	} else {
		resp.Message = fmt.Sprintf("Hello %s.", in.Name)
	}
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
