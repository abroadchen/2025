package nsq

import (
	"fmt"
	"github.com/nsqio/go-nsq"
	"slave-server/webPageGet/GetMail"
)

type MyConsumer struct {
	cs *nsq.Consumer
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

	go func() {
		maillist := GetMail.GetMail(string(msg.Body))
		for _, mail := range maillist {
			myp := NewMyProduct()
			myp.Pub("Email", mail)
		}
	}()
	return nil
}
