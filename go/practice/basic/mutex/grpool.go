/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"fmt"
	"github.com/ivpusic/grpool"
	"log"
	"time"
)

func main() {
	pool := grpool.NewPool(20, 50)
	pool.WaitCount(50)

	fn := func(i int) {
		fmt.Println("start job", i)
		time.Sleep(time.Duration(i) * time.Second)
		fmt.Println("end job", i)
	}

	for i := 0; i < 10; i++ {
		i := i
		pool.JobQueue <- func() {
			fn(i)
		}
	}

	log.Println("Submitted")

	pool.WaitAll()

	pool.Release()
}
