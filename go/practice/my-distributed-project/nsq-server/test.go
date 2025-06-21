package main

import (
	"fmt"
	"github.com/nsqio/go-nsq"
	"strconv"
	"time"
)

type MyProduct struct {
	Pd *nsq.Producer
}

func NewMyProduct() *MyProduct {
	product, err := nsq.NewProducer("127.0.0.1:4150", nsq.NewConfig())
	if err != nil {
		fmt.Println(err)
	}
	err = product.Ping()
	if err != nil {
		return nil
	}
	return &MyProduct{product}
}

func (myProduct *MyProduct) Pub(topic string, msg string) error {
	err := myProduct.Pd.Publish(topic, []byte(msg))
	return err
}

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
	return nil
}

func main() {
	for i := 0; i < 3; i++ {
		go func(j int) {
			myProduct := NewMyProduct()
			for i := 0; i < 100; i++ {
				myProduct.Pub("xx", "test_topic_"+strconv.Itoa(i)+strconv.Itoa(j))
			}
		}(i)
	}
	for i := 0; i < 2; i++ {
		go func(j int) {
			myConsumer := NewMyConsumer("xx", "chanel")
			fmt.Println(myConsumer, j)
		}(i)
	}
	time.Sleep(time.Hour)
}
