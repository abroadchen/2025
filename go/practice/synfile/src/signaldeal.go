package main

import (
	"fmt"
	"time"
)

func main() {
	c, quit := make(chan int), make(chan int)
	go func() {
		c <- 2
		time.Sleep(time.Second * 10)
		quit <- 1
	}()
	for isok := false; !isok; {
		select {
		case v := <-c:
			fmt.Println("received data", v)
		case <-quit:
			fmt.Println("received quit signal")
			isok = true
		}
	}
}
