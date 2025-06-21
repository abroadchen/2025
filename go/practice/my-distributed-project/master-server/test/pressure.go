package test

import (
	"fmt"
	"math/rand"
	"my-distributed-project/store/savetxt"
	"my-distributed-project/thread"
	"sync"
	"time"
)

func main() {
	var data chan int
	var sf = savetxt.NewSafeFile("savemail.txt")
	go thread.CheckThreadNum()
	url := ""
	var wg sync.WaitGroup
	num := 0
	for i := 0; i < 10000; i++ {
		for j := 0; j < 10000; j++ {
			wg.Add(1)
			go func() {
				thread.GetMailThread(sf, url, &wg)
				time.Sleep(time.Second * time.Duration(rand.Uint64()%500+3))
			}()
			num += 1
		}
		fmt.Println("thread num:", num)
		time.Sleep(time.Second)
	}
	wg.Wait()
	fmt.Println("done")
	<-data
}
