package mem

import (
	"master-server/datastruct/queue"
	"master-server/staticdata"
	"master-server/webPageGet/GetURL"
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
