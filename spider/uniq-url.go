package spider

import (
	"container/list"
	"fmt"
	"sync/atomic"
	"time"
)

func main() {
	urlmap := make(map[string]int)
	url := ""

	go func() {
		for {
			fmt.Println("现在有", atomic.LoadInt32(&threadnum), "个线程还在")
			time.Sleep(10 * time.Second)
		}
	}()
	myqueue := list.New()
	myqueue.PushBack(url)

	level := 0
	for myqueue.Len() != 0 {
		myurl := myqueue.Front()
		//fmt.Println(myurl.Value.(string))
		go GetEmail(myurl.Value.(string), &threadnum)

		myqueue.Remove(myurl)
		urllist := GetURL(myurl.Value.(string))
		for _, geturl := range urllist {
			_, ok := urlmap[geturl]
			if ok {
				urlmap[geturl]++
			} else {
				urlmap[geturl] = 1
				myqueue.PushBack(geturl)
			}
		}
		level++
		if level > 1000 {
			break
		}
	}
	for k, v := range urlmap {
		fmt.Println(k, v)
	}
}
