package spider

import (
	"container/list"
	"fmt"
)

func Bfs() {
	url := ""
	myqueue := list.New()
	myqueue.PushBack(url)

	level := 0
	for myqueue.Len() != 0 {
		myurl := myqueue.Front()
		fmt.Println(myurl.Value.(string))
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
}
