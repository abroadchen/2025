package thread

import (
	"sync"
	"time"
)

func GetURLThread(url string, queue *queue.Queue, sf *savetxt.SafeFile, wg *sync.WaitGroup) {
	urllist := GetURL.GetURL(url)
	var wgx sync.WaitGroup
	for i := 0; i < len(urllist); i++ {
		isok := staticdata.Urlmap.Isin(urllist[i])
		if isok {
			num := staticdata.Urlmap.Get(urllist[i])
			staticdata.Urlmap.Set(urllist[i], num)
		} else {
			staticdata.Urlmap.Set(urllist[i], 1)
			//lastlist = append(lastlist, urllist[i])
			queue.Enqueue(urllist[i])
			if staticdata.ThreadNum < staticdata.MAXTHREADNUM {
				wgx.Add(1)
				go GetMailThread(sf, urllist[i], &wgx, queue)
			} else {
				GetMailThread(sf, urllist[i], &wgx, queue)
			}
		}
	}
	wgx.Wait()
	time.Sleep(time.Second * 10)
}
