package main

import (
	"fmt"
	"time"
)

func foot(i int) chan int {
	c := make(chan int)
	go func() {
		c <- i
	}()
	return c
}

func main() {
	c1, c2, c3 := foot(1), foot(10), foot(100)
	timeout := time.After(time.Second)
	for is_timeout := false; !is_timeout; {
		select {
		case v1 := <-c1:
			fmt.Println("received", v1)
		case v2 := <-c2:
			fmt.Println("received", v2)
		case v3 := <-c3:
			fmt.Println("received", v3)
		case <-timeout:
			fmt.Println("timeout")
			is_timeout = true
		}
	}
}
