/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"fmt"
	"github.com/gammazero/workerpool"
	"log"
	"time"
)

func main() {
	wp := workerpool.New(20)

	fn := func(i int) {
		fmt.Println("start job", i)
		time.Sleep(time.Duration(i) * time.Second)
		fmt.Println("end job", i)
	}

	for i := 0; i < 10; i++ {
		i := i
		wp.Submit(func() {
			fn(i)
		})
	}

	log.Println("finish job")
	wp.StopWait()
}
