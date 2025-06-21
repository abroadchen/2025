package main

import (
	"fmt"
	"math/rand"
	"time"
)

func do_file(x int) int {
	time.Sleep(time.Duration(rand.Intn(10)) * time.Second)
	return 1000 - x
}

func Branch(x int) chan int {
	ch := make(chan int)
	go func() {
		ch <- do_file(x)
	}()
	return ch
}

func FanIn(chs ...chan int) chan int {
	ch := make(chan int)
	for _, c := range chs {
		go func(c chan int) {
			ch <- <-c
		}(c)
	}
	return ch
}

func main() {
	res := FanIn(Branch(1), Branch(10), Branch(100))
	for i := 0; i < 3; i++ {
		fmt.Println(<-res)
	}
}
