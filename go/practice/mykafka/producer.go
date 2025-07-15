/*
Package mykafka

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package mykafka

import (
	"fmt"
	"github.com/Shopify/sarama"
)

func SendMessageKafka(pipname string, sendmsg string) {
	config := sarama.NewConfig()
	config.Producer.RequiredAcks = sarama.WaitForAll
	config.Producer.Partitioner = sarama.NewRandomPartitioner
	config.Producer.Return.Successes = true

	producer, err := sarama.NewSyncProducer([]string{"192.168.18.101:9092"}, config)
	if err != nil {
		fmt.Println(err)
	}
	defer producer.Close()
	msg := &sarama.ProducerMessage{
		Topic:     "test",
		Partition: int32(0),
		Key:       sarama.StringEncoder("test"),
	}

	//for {
	var value string = sendmsg
	var msgType string = pipname
	_, err := fmt.Scanf("%s", &value)
	if err != nil {
		break
	}
	fmt.Scanf("%s", &msgType)
	fmt.Printf("%s: %s\n", msgType, value)
	msg.Topic = msgType
	msg.Value = sarama.ByteEncoder(value)

	partition, offset, err := producer.SendMessage(msg)

	if err != nil {
		fmt.Println(err)
	}
	fmt.Printf("Partition: %d, Offset: %d\n", partition, offset)
	//}
}

var taskchan = make(chan string, 100)

func main() {
	go func() {
		for {
			mystr := <-taskchan
			SendMessageKafka("test", mystr)
		}
	}()
}
