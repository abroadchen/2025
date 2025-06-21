package main

import (
	"fmt"
	"github.com/nsqio/go-nsq"
	"time"
)

type NsqHandler struct {
	msqCount     int64
	NsqHandlerID string
}

func (h *NsqHandler) HandleMessage(msg *nsq.Message) error {
	h.msqCount += 1
	fmt.Println(h.msqCount, h.NsqHandlerID, time.Now())
	time.Sleep(time.Second)
	return nil
}

func main() {
	var tcpnsqaddr = "127.0.0.1:4150"
	config := nsq.NewConfig()
	com, err := nsq.NewConsumer("my_topic", "my_channel", config)
	if err != nil {
		fmt.Println(err)
	}
	com.AddHandler(&NsqHandler{NsqHandlerID: "One"})
	err = com.ConnectToNSQD(tcpnsqaddr)
	if err != nil {
		fmt.Println(err)
	}
	time.Sleep(100 * time.Second)
}
