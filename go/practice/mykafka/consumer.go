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
	"sync"
)

func GetMsgDokafka(myfunc func(getmsg string)) {
	var wg sync.WaitGroup
	consumer, err := sarama.NewConsumer([]string{"192.168.18.101:9092"}, nil)
	if err != nil {
		panic(err)
	}
	partitionList, err := consumer.Partitions("test")
	if err != nil {
		panic(err)
	}
	fmt.Println(partitionList)
	for partition := range partitionList {
		pc, err := consumer.ConsumerPartition("test", int32(partition), sarama.OffsetNewest)
		if err != nil {
			panic(err)
		}
		defer pc.AsyncClose()
		wg.Add(1)
		go func(sarama.ParitionConsumer) {
			defer wg.Done()
			fmt.Println("ok1")
			for msg := range pc.Messages() {
				fmt.Printf("%s---partition:%d,offset:%d,key:%s,value:%s\n", msg.Topic, msg.Partition, msg.Offset, string(msg.Key), string(msg.Value))
				myfunc(string(msg.Value))
			}
			fmt.Println("ok2")
		}(pc)
	}
	wg.Wait()
	consumer.Close()
}
