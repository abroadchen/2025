package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	rand.Seed(100)
	nworks := 8
	work := make(chan Request, 100)
	balancer := new_balancer(nworks, work)
	balancer.start()
	balancer.balance(work)
	for i := 0; i < 100; i++ {
		requester(work)
	}
	go func() {
		for _ = range time.Tick(250 * time.Millisecond) {
			balancer.print()
		}
	}()
	time.Sleep(10 * time.Second)
	fmt.Println("%d work over", counter)
}
