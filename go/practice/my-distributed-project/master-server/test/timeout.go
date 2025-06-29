package test

import (
	"container/list"
	"fmt"
	"sync/atomic"
	"time"
)

func main() {

	ch := make(chan string)
	go func() {
		time.Sleep(3 * time.Second)
		ch <- "meowwo"
	}()
	select {
	case msg := <-ch:
		fmt.Println(msg)
	case <-time.After(1 * time.Second):
		fmt.Println("timeout")
	}
}

var ThreadNum int32 = 0

func main2() {

	Getmailmap := func(url string) {
		
	}

	go func() {
		for {
			time.Sleep(4 * time.Second)
			fmt.Println("此时此刻还有", ThreadNum, "个线程还活着")
		}
	}()

	url := ""
	myqueue := list.New()
	myqueue.PushBack(url)
	for myqueue.Len() != 0 {
		myurl := myqueue.Front()
		go func() {
			atomic.AddInt32(&ThreadNum, 1)
			ch := make(chan string)
			go func() {
				Getmailmap(myrurl.Value.(string))
				ch <- "ok"
			}()
			select {
			case msg := <-ch:
				fmt.Println(msg)
			case <-time.After(2 * time.Second):
				fmt.Println("timeout")
			}
			atomic.AddInt32(&ThreadNum, -1)
		}()
	}

}
