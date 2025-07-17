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
	ch := make(chan int, 10)
	var i = 0

	for ; i < 10; i++ {
		ch <- i
	}

	go func() {
		for {
			i++
			ch <- i
		}
	}()

	for j := 0; j < 50; j++ {
		time.Sleep(time.Second)
		k := <-ch
		fmt.Println(k)
	}
}
