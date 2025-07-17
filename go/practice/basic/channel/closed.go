/*
Package channel

	@author: June
	@since: 2025/7/17
	@desc:
*/
package channel

import (
	"fmt"
	"time"
)

func receive() {
	ch := make(chan int, 100)
	for i := 0; i < 10; i++ {
		ch <- i
	}
	close(ch)

	for {
		i, ok := <-ch
		fmt.Println("receive", i, ok)
		time.Sleep(time.Second)
	}
}
