package main

import (
	"fmt"
	"time"
)

func timer(d time.Duration) chan bool {
	ch := make(chan bool)
	go func() {
		time.Sleep(d)
		ch <- true
	}()
	return ch
}

func main() {
	timeout := timer(time.Second * 5)
	for {
		select {
		case <-timeout:
			fmt.Println("time over")
			return
		}
	}
}
