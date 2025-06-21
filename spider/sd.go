package spider

import (
	"container/list"
	"fmt"
)

func Dfs() {
	url := ""
	mystack := list.New()
	mystack.PushBack(url)

	level := 0
	for mystack.Len() != 0 {
		myurl := mystack.Back()
		fmt.Println(myurl.Value.(string))
		mystack.Remove(myurl)
		urllist := GetURL(myurl.Value.(string))
		for _, geturl := range urllist {
			mystack.PushBack(geturl)
		}
		level++
		if level > 1000 {
			break
		}
	}
}
