package nsq

import "fmt"

func NSQThread() {
	myc := NewMyConsumer("Log", "")
	fmt.Println(myc)
	mychan := make(chan int)
	<-mychan
}
