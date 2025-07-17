/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"fmt"
	"time"
)

func main() {
	var ch = make(chan int, 3)
	var done = make(chan struct{})

	go func() {
		for {
			select {
			case <-done:
				return
			case i := <-ch:
				fmt.Println("i", i)
			}
		}
	}()

	go func() {
		for i := 0; i < 10; i++ {
			select {
			case <-done:
				return
			case ch <- i:
			}
			time.Sleep(time.Millisecond * 100)
		}
	}()
}
