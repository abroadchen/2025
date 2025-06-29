package client

import (
	"fmt"
	"google.golang.org/grpc"
	"strings"
)

func GetQQlistbyQQqun(QQqun int) []string {
	Address := "127.0.0.1:51001"
	conn, err := grpc.Dial(Address, grpc.WithInsecure())
	if err != nil {
		fmt.Println(err)
	}
	defer conn.Close()

	fmt.Println(res.Message)
	mystrlist := []string{}
	mylist := strings.Split(res.Message, "&^&")
	for _, line := range mylist {
		mystrlist = append(mystrlist, line)
	}
	return mystrlist
}
