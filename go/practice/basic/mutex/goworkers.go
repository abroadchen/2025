/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"fmt"
	"github.com/dpaks/goworkers"
	"log"
	"time"
)

func main() {
	opts := goworkers.Options{
		Workers: 20,
	}
	gw := goworkers.New(opts)

	fn := func(i int) {
		fmt.Println("start job", i)
		time.Sleep(time.Duration(i) * time.Second)
		fmt.Println("finish job", i)
	}

	for i := 0; i < 10; i++ {
		i := i
		gw.Submit(func() {
			fn(i)
		})
	}
	log.Println("Submitted")

	gw.Stop(true)
}
