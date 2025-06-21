package main

import "fmt"

func foo(i int) chan int {
	ch := make(chan int)
	go func() {
		ch <- i
	}()
	return ch
}

func main() {
	c1, c2, c3 := foo(1), foo(2), foo(3)
	c := make(chan int)
	go func() {
		for {
			select {
			case v1 := <-c1:
				c <- v1
			case v2 := <-c2:
				c <- v2
			case v3 := <-c3:
				c <- v3
			}
		}
	}()
	for i := 0; i < 3; i++ {
		fmt.Println(<-c)
	}
}
