package test

import (
	"container/list"
	"fmt"
	"time"
)

func main() {
	urlchan := make(chan string, 1000)

	go func() {
		url := ""
		myqueue := list.New()
		myqueue.PushBack(url)

		level := 0
		for myqueue.Len() != 0 {
			myurl := myqueue.Front()
			//fmt.Println(myurl.Value.(string))
			urlchan <- myurl.Value.(string)
			myqueue.Remove(myurl)
			urllist := GetURL(myurl.Value.(string))
			for _, geturl := range urllist {
				myqueue.PushBack(geturl)
			}
			level++
			if level > 1000 {
				break
			}
		}
	}()

	for i := 0; i < 5; i++ {
		go func(id int) {
			for {
				if elem, ok := <-urlchan; ok {
					fmt.Println(id, "收到url", elem)
					emaillist := GetMail(elem)
					for _, email := range emaillist {
						fmt.Println(id, "<UNK>", email)
					}
				} else {
					fmt.Println("urlchain已关闭")
					break
				}
			}
		}()
	}
	time.Sleep(time.Second * 100)
}
