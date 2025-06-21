package thread

import (
	"container/list"
	"fmt"
	"master-server/datastruct/queue"
	"master-server/staticdata"
	"master-server/webPageGet/GetURL"
	"time"
)

func URLDeduplication(url string) []string {
	urllist := GetURL.GetURL(url)
	lastlist := []string{}
	for i := 0; i < len(urllist); i++ {
		isok := staticdata.Mailmap.Isin(urllist[i])
		if isok {
			num := staticdata.Mailmap.Get(urllist[i])
			staticdata.Mailmap.Set(urllist[i], num+1)
		} else {
			staticdata.Mailmap.Set(urllist[i], 1)
			lastlist = append(lastlist, urllist[i])
		}
	}
	return lastlist
}

func MakeURLThread(url string) {
	q := queue.Queue{make(chan string, 10000)}
	q.Enqueue(url)
	for len(q.Items) != 0 {
		myurl := q.Dequeue()
		staticdata.Urlchan <- myurl
		urllist := URLDeduplication(myurl)
		for _, geturl := range urllist {
			q.Enqueue(geturl)
			staticdata.Urlchan <- geturl
		}
	}
}

func MakeURLtoURLChan(url string) {
	myqueue := list.New()
	myqueue.PushBack(url)
	i := 0
	for myqueue.Len() != 0 {
		myurl := myqueue.Front()
		mystr := myurl.Value.(string)
		mystrlen := len(mystr)
		mybytes := IntToBytes(mystrlen)
		conns[i%len(conns)].Write(mybytes)
		conns[i%len(conns)].Write([]byte(mystr))
		//randnum, _ := rand.Int()
		//conns[randnum%len(conns)].Write(mybytes)
		//conns[randnum%len(conns)].Write([]byte(mystr))
		myqueue.Remove(myurl)
		urllist := GetURL.GetURL(myurl.Value.(string))
		for _, url := range urllist {
			myqueue.PushBack(url)
			//mystr := url
			//mystrlen := len(mystr)
			//mybytes := IntToBytes(mystrlen)
			//conn.Write(mybytes)
			//conn.Write([]byte(mystr))
		}
		i++
	}
}

func MakeURLforNSQ(url string) {
	myp := nsq.NewProducer()
	q := queue.Queue{make(chan string, 1000)}
	q.Enqueue(url)
AAA:
	for len(q.Items) != 0 {
		myurl := q.Dequeue()
		fmt.Println("push", myurl)
		myp.Pub("URL", myurl)
		urllist := URLDeduplication(myurl)
		for _, url := range urllist {
			q.Enqueue(url)
			fmt.Println("push", url)
			myp.Pub("URL", url)
		}
	}
	time.Sleep(time.Second)
	goto AAA
	fmt.Println("done")
}
