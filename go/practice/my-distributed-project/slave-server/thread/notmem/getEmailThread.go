package notmem

import (
	"fmt"
	"slave-server/staticdata"
	"slave-server/thread/network"
	"slave-server/webPageGet/GetMail"
	"sync/atomic"
	"time"
)

func GetMailThreadGo(r network.ReturnEmail, url string) {
	maillist := GetMail.GetMail(url)
	r.SaveMails(maillist)
}

func GetMailThread(r network.ReturnEmail, url string) {
	atomic.AddInt64(&staticdata.ThreadNum, 1)
	ch := make(chan string)
	go func() {
		GetMailThreadGo(r, url)
		ch <- "ok"
	}()
	select {
	case msg := <-ch:
		fmt.Println(msg)
	case <-time.After(5 * time.Second):
		//fmt.Println("timeout")
		time.Sleep(time.Second)

	}
	atomic.AddInt64(&staticdata.ThreadNum, -1)
}
