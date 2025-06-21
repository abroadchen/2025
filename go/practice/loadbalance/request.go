package main

import (
	"fmt"
	"math/rand"
	"time"
)

var counter int

type Request struct {
	fn func() int
	c  chan int
}

func requester(work chan Request) {
	c := make(chan int, 100)
	go func() {
		for {
			time.Sleep(time.Microsecond * time.Duration(rand.Int63n(10)))
			work <- Request{do_some_work, c}
			result := <-c
			do_important_work(result)
		}
	}()
}

func do_some_work() int {
	counter++
	time.Sleep(time.Microsecond * time.Duration(rand.Int63n(10)))
	return counter
}

func do_important_work(r int) {
	fmt.Println(r)
}
