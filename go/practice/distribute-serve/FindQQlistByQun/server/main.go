package server

import (
	"fmt"
	"log"
	"strconv"
)

const (
	Address = "localhost:50052"
)

type helloService struct{}

var HelloService = helloService{}

func (h helloService) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	resp := new(pb.HelloResponse)
	qunnumstr := fmt.Sprintf("%s", in.Name)
	qunnum, _ := strconv.Atoi(qunnumstr)
	log.Println("qunnum", qunnum)

	myQQlist := bin_searchQQ(Qfindx, Qfii, qunnum)

	mystr := ""
	for _, QQ := range myQQlist {
		mystr = mystr + QQ
		mystr += "&^&"
	}
	resp.Message = fmt.Sprintf("%s", mystr)
	return resp, nil
}
