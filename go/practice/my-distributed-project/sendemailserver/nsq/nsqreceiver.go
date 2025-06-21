package nsq

import (
	"fmt"
	"sendemailserver/sendemail"
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
		mysend := sendemail.NewSendEmail()
		isok := mysend.Send()
		myp := NewMyProduct()
		if isok {
			myp.Pub("SendResult", string(msg.Body)+"$#$"+"1")
		} else {
			myp.Pub("SendResult", string(msg.Body)+"$#$"+"0")
		}
		//maillist := GetMail.GetMail(string(msg.Body))
		//for _, mail := range maillist {
		//	myp := NewMyProduct()
		//	myp.Pub("SendResult", mail)
		//}
	}()
	return nil
}
