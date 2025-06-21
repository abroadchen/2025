package main

import (
	"fmt"
	"time"
)

type Message struct {
	str   string
	block chan int
}

func Fanin(ch1, ch2 <-chan Message) <-chan Message {
	newch := make(chan Message)
	go func() {
		for {
			newch <- <-ch1
		}
	}()
	go func() {
		for {
			newch <- <-ch2
		}
	}()
	return newch
}

func Generator(msg string) <-chan Message {
	ch := make(chan Message)
	blockingStep := make(chan int)
	go func() {
		for i := 0; ; i++ {
			ch <- Message{fmt.Sprintf("%s %d", msg, i), blockingStep}
			time.Sleep(time.Second)
			blockingStep <- 1
		}
	}()
	return ch
}

func main() {
	ch := Fanin(Generator("hello world"), Generator("hello world"))
	for i := 0; i < 10; i++ {
		mgs1 := <-ch
		fmt.Println(mgs1.str)
		mgs2 := <-ch
		fmt.Println(mgs2.str)
		<-mgs1.block
		<-mgs2.block

	}
}
