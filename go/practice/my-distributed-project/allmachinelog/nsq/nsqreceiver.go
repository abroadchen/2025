package nsq

import (
	"allmachinelog/log"
	"allmachinelog/static"
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
	SaveData(string(msg.Body))
	return nil
}

func SaveData(logstr string) {
	var id int = static.Id
	var addr string
	var time string
	var info string
	var level int
	mylist := strings.Split(logstr, ",")
	addr = mylist[0]
	time = mylist[1]
	info = mylist[2]
	level, _ = strconv.Atoi(mylist[3])
	myloginfo := log.NewLogInfo(id, addr, time, info, level)
	static.Mydb.Add(myloginfo)
	id++
}
