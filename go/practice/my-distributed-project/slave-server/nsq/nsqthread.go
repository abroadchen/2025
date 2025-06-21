package nsq

func NSQThread() {
	myc := NewMyConsumer("URL", "")

	mychan := make(chan int)
	<-mychan
}
