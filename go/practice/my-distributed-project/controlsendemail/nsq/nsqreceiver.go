package nsq

import (
	"fmt"
	"github.com/nsqio/go-nsq"
	"strconv"
	"strings"
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
	mystr := string(msg.Body)
	mylist := strings.Split(mystr, "$#$")
	if len(mylist) == 2 {
		num, err := strconv.Atoi(mylist[1])
		if err != nil {
			return err
		}
		if num != 0 {
			mydb.UpdateSendEmailStat(mylist[0], num)
		}
	}
	return nil
}
