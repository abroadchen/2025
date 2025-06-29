package test

import (
	"sync/atomic"
	"time"
)

var money int32 = 0

func add(pint *int32) {
	for i := 0; i < 100000; i++ {
		atomic.AddInt32(pint, 1)
	}
}

func main() {
	for i := 0; i < 1000; i++ {
		go add(&money)
	}
	time.Sleep(10 * time.Second)
}
