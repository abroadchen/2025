package ReadMsgQueue

import (
	"fmt"
	"github.com/nsqio/go-nsq"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/grpclog"
	"sendemailserver/sendemail"
)

var num int = 0
var myAddress []string = []string{"127.0.0.1:50051", "127.0.0.1:50052", "127.0.0.1:50053"}

type MyConsumer struct {
	cd *nsq.Consumer
}

func NewMyConsumer(topic string, chanel string) *MyConsumer {
	consumer, err := nsq.NewConsumer(topic, chanel, nsq.NewConfig())
	if err != nil {
		fmt.Println(err)
	}
	consumer.AddHandler(&MyConsumer{})
	err = consumer.ConnectToNSQD("127.0.0.1:4150")
	if err != nil {
		fmt.Println(err)
	}
	return &MyConsumer{consumer}
}

func (MyConsumer *MyConsumer) HandleMessage(msg *nsq.Message) error {
	fmt.Printf("MyConsumer receive a message: %s", msg.Body)
	Send(myAddress[num%len(myAddress)], mystr)
	num++
	return nil
}

const (
	Address = "localhost:50072"
)

type helloService struct{}

var HelloService = helloService{}

func (h helloService) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	resp := new(pb.HelloResponse)
	if in.Name == "start" {
		myc := NewMyConsumer("ToSend", "chanel")
		fmt.Println(myc)
	}
	resp.Message = fmt.Sprintf("Hello %s.", in.Name)
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
