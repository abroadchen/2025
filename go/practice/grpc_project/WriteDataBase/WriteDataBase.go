package WriteDataBase

import (
	"fmt"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/grpclog"
	"strconv"
	"strings"
)

const (
	Address = "localhost:50022"
)

type helloService struct{}

var HelloService = helloService{}

func (h helloService) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	resp := new(pb.HelloResponse)
	mystr := string(in.Name)
	mylist := strings.Split(mystr, "$#$")
	if len(mylist) == 2 {
		num, err := strconv.Atoi(mylist[1])
		if err != nil {
			fmt.Println(err)
		}
		if num != 0 {
			mydb.UpdateSendEmailStat(mylist[0], num)
		}
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
