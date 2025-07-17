/*
Package ratelimit

	@author: June
	@since: 2025/7/17
	@desc:   golang.org/x/time/rate go.uber.org/ratelimit
*/
package ratelimit

import (
	"fmt"
	"github.com/juju/ratelimit"
	"time"
)

func main() {
	limit()
	fmt.Printf("\n")

	limitWithQuantum()
	fmt.Println()

	limitWithRate()
	fmt.Println()
}

func limit() {
	rl := ratelimit.NewBucket(10*time.Millisecond, 1)
	fmt.Println("run limit rate: ", rl.Rate())

	for i := 0; i < 10; i++ {
		start := time.Now()
		rl.Wait(1)
		fmt.Printf("%v\n", time.Since(start))
	}
}

func limitWithQuantum() {

}
