/*
Package cond2

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package cond2

import (
	"log"
	"math/rand"
	"sync"
	"time"
)

func main() {
	c := sync.NewCond(&sync.Mutex{})

	var ready int

	for i := 0; i < 10; i++ {
		go func(i int) {
			time.Sleep(time.Duration(rand.Int63n(2)) * time.Second)

			c.L.Lock()
			ready++
			c.L.Unlock()

			log.Printf("%d started\n", i)
			//log.Printf("#{i} started\n")
			c.Broadcast()
		}(i)
	}

	c.L.Lock()
	for ready != 10 {
		c.Wait()
		log.Printf("裁判员被唤醒一次")
	}
	c.L.Unlock()

	log.Printf("所有运动员都准备就绪 比赛开始 3,2,1,...")

	time.Sleep(time.Second)
}
