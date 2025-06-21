package nsqserver

import (
	"data-server/database"
	"data-server/staticdata"
	"fmt"
	"github.com/nsqio/go-nsq"
	"strconv"
)

type MyConsumer struct {
	Cs *nsq.Consumer
}

func NewMyConsumer(topic string, chanel string, saveDatafuncs []database.SaveData) *MyConsumer {
	consumer, err := nsq.NewConsumer(topic, chanel, nsq.NewConfig())
	if err != nil {
		fmt.Println(err)
	}
	consumer.AddHandler(&MyConsumer{})
	err = consumer.ConnectToNSQD("127.0.0.1:4150")
	if err != nil {
		fmt.Println(err)
	}
	mycon := new(MyConsumer)
	for _, save := range saveDatafuncs {
		staticdata.SaveDatafuncs = append(staticdata.SaveDatafuncs, save)
	}
	mycon.Cs = consumer
	return mycon
}

func (MyConsumer *MyConsumer) HandleMessage(msg *nsq.Message) error {
	fmt.Printf("MyConsumer receive a message: %s", msg.Body)
	MyConsumer.Save(string(msg.Body))
	return nil
}

func (MyConsumer *MyConsumer) Save(mail string) {

	emailstr := mail
	isok := staticdata.Mailmap.Isin(emailstr)
	if isok {
		num := staticdata.Mailmap.Get(emailstr)
		numint, _ := strconv.Atoi(num)
		staticdata.Mailmap.Set(emailstr, strconv.Itoa(1+numint))
	} else {
		staticdata.Mailmap.Set(emailstr, strconv.Itoa(1))
		fmt.Println("take", emailstr)
		for _, saveData := range staticdata.SaveDatafuncs {
			saveData.WriteLine(mail)
		}
	}
}
