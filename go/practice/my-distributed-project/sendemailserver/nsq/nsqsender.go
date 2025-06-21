package nsq

import (
	"fmt"
	"github.com/nsqio/go-nsq"
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
