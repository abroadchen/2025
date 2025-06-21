package thread

import (
	"fmt"
	"master-server/data-server/store/savetxt"
	"master-server/datastruct/queue"
	"master-server/staticdata"
	"slave-server/webPageGet/GetMail"
	"sync"
	"sync/atomic"
	"time"
)

func GetMailThreadGo(safefile *savetxt.SafeFile, url string) {
	maillist := GetMail.GetMail(url)
	lastlist := []string{}
	for i := 0; i < len(maillist); i++ {
		isok := staticdata.Urlmap.Isin(maillist[i])
		if isok {
			num := staticdata.Urlmap.Get(maillist[i])
			staticdata.Urlmap.Set(maillist[i], num)
		} else {
			staticdata.Urlmap.Set(maillist[i], 1)
			lastlist = append(lastlist, maillist[i])
		}
	}
	safefile.WriteLines(lastlist)
}

func GetMailThread(safefile *savetxt.SafeFile, url string, wg *sync.WaitGroup, queue *queue.Queue) {
	atomic.AddInt64(&staticdata.ThreadNum, 1)
	ch := make(chan string)
	go func() {
		GetMailThreadGo(safefile, url)
		ch <- "ok"
	}()
	select {
	case msg := <-ch:
		fmt.Println(msg)
	case <-time.After(2 * time.Second):
		//fmt.Println("timeout")
		time.Sleep(time.Second)
		queue.Enqueue(url)
	}
	atomic.AddInt64(&staticdata.ThreadNum, -1)
	wg.Done()
}
