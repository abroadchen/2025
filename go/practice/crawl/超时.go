package crawl

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	intChan := make(chan int, 1)
	go func() {
		for i := 0; i < 10; i++ {
			time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
			intChan <- i
		}
	}()
	timeout := time.Second * 5
	var timer *time.Timer
	timeAferC := <-time.After(100 * time.Millisecond)
	fmt.Println("timeAfterC", timeAferC)
	time.AfterFunc(2*time.Second, func() {
		fmt.Println("2秒后执行")
	})

	for {
		if timer == nil {
			timer = time.NewTimer(timeout)
		} else {
			timer.Reset(timeout)
		}

		select {
		case e, ok := <-intChan:
			if !ok {
				fmt.Println("received end")
				return
			} else {
				fmt.Println("received", e)
			}
		case <-timer.C:
			fmt.Println("timeout")
			return
		}
	}
}
