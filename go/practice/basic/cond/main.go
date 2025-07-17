/*
Package cond

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package cond

import (
	"log"
	"math/rand"
	"sync"
	"time"
)

func main() {
	var m sync.Mutex
	c := sync.NewCond(&m)

	ready := make(chan struct{}, 10)
	isReady := false

	for i := 0; i < 10; i++ {
		i := i
		go func() {
			m.Lock()
			time.Sleep(time.Duration(rand.Int63n(2)) * time.Second)
			ready <- struct{}{}
			for !isReady {
				c.Wait()
			}
			log.Printf("%d started\n", i)
			//log.Printf("#{i} started\n")
			m.Unlock()
		}()
	}

	c.Broadcast()

	for i := 0; i < 10; i++ {
		<-ready
	}

	m.Lock()
	isReady = true
	c.Broadcast()
	m.Unlock()

	time.Sleep(time.Second)
}
