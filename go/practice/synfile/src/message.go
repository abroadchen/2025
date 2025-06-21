package main

import (
	"fmt"
	"math/rand"
	"time"
)

func processUsers() {
	i := 0
	ch := make(chan string, 4)
	go func() {
		fmt.Println("go routine say", <-ch)
	}()
	for true {
		go processUser(i, ch)
		time.Sleep(time.Duration(200+rand.Intn(200)) * time.Millisecond)
		i++
	}
}

func processUser(userID int, ch chan string) {
	ch <- fmt.Sprintf("I'm processing user %d", userID)
	fmt.Println("message", userID, "was sent")
}

func fanInMultiplex(inputs ...chan string) chan string {
	c := make(chan string)
	for _, in := range inputs {
		go func(curr chan string) {
			c <- <-curr
		}(in)
	}
	return c
}

func main2() {
	go processUsers()
	time.Sleep(3 * time.Second)
}

func main() {
	n := 10
	leftmost := make(chan int)
	left, right := leftmost, leftmost
	for i := 0; i < n; i++ {
		right = make(chan int)
		go gopher(left, right)
		left = right
	}
	go func(c chan int) {
		c <- 1
	}(right)
	fmt.Println(<-leftmost)
}

func gopher(left, right chan int) {
	left <- 1 + <-right
}
