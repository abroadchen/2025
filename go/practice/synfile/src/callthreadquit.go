package main

import (
	"context"
	"fmt"
	"github.com/scottkiss/grtm"
	"time"
)

func myfunc() {
	fmt.Println("I'm busy")
	i := 0
	for {
		i++
		fmt.Println("I'm busy", i)
		time.Sleep(time.Second)
	}
}

func main() {
	gm := grtm.NewGrManager()
	gm.NewLoopGoroutine("myfunc", myfunc)
	time.Sleep(time.Second * 30)
	gm.StopLoopGoroutine("myfunc")
	time.Sleep(time.Second * 100)

	stop := make(chan bool)
	go func() {
		i := 0
		for {
			select {
			case <-stop:
				fmt.Println("quit")
				return
			default:
				fmt.Println("watching")
				i++
				time.Sleep(time.Second)
			}
		}
	}()
	time.Sleep(time.Second * 10)
	stop <- true
	time.Sleep(time.Second * 5)

	ctx, cancel := context.WithCancel(context.Background())
	go func(ctx context.Context) {
		i := 0
		for {
			select {
			case <-ctx.Done():
				fmt.Println("watching quit")
				return
			default:
				fmt.Println("working", i)
				i++
				time.Sleep(time.Second)
			}
		}
	}(ctx)
	time.Sleep(time.Second * 10)
	cancel()
	time.Sleep(time.Second * 5)

	ctx1, cancel1 := context.WithCancel(context.Background())
	go Watch(ctx1, "A")
	go Watch(ctx1, "B")
	go Watch(ctx1, "C")
	time.Sleep(time.Second * 10)
	cancel1()
	time.Sleep(time.Second * 5)
}

func Watch(ctx context.Context, name string) {
	i := 0
	for {
		select {
		case <-ctx.Done():
			fmt.Println("quit", name)
			return
		default:
			fmt.Println(name, "watching", i)
			i++
			time.Sleep(time.Second)
		}
	}
}
