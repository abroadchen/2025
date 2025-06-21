package nsq

import "fmt"

func NSQThread() {
	myc := NewMyConsumer("ToSend", "chanel")
	fmt.Println(myc)
	mychan := make(chan int)
	<-mychan
}
