package main

import (
	"fmt"
	"github.com/nsqio/go-nsq"
	"strconv"
)

func main() {
	var tcpnsqaddr = "127.0.0.1:4150"
	config := nsq.NewConfig()
	for i := 0; i < 100; i++ {
		tPro, err := nsq.NewProducer(tcpnsqaddr, config)
		if err != nil {
			fmt.Println(err)
		}
		topic := "Email"
		tData := "xxx" + strconv.Itoa(i) + "@qq.com"
		err = tPro.Publish(topic, []byte(tData))
		if err != nil {
			fmt.Println(err)
		}
	}
}
