package GetURL

import (
	"slave-server/datastruct/myMap"
	"slave-server/store/savetxt"
)

func Deduplicate(xmap *myMap.MyMap, xlist []string, sf *savetxt.SafeFile) {
	lastlist := []string{}
	for i := 0; i < len(xlist); i++ {
		isok := xmap.Isin(xlist[i])
		if isok {
			num := xmap.Get(xlist[i])
			xmap.Set(xlist[i], num)
		} else {
			xmap.Set(xlist[i], 1)
			lastlist = append(lastlist, xlist[i])
		}
	}
	//for _, lasturl := range lastlist {
	//	queue.Queue.Enqueue(lasturl)
	//	go thread.GetMailThread(sf, lasturl)
	//}
}
