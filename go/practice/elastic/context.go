/*
Package main

	@author: chen
	@since: 2025/7/15
	@desc: 合理结束线程
*/
package main

import (
	"context"
	"fmt"
	"time"
)

// main
//
//	@Description:
func main1() {
	gen := func(ctx context.Context) <-chan int {
		dst := make(chan int)
		n := 1
		go func() {
			for {
				select {
				case <-ctx.Done():
					return
				case dst <- n:
					n++
				}
			}
		}()
		return dst
	}

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	for n := range gen(ctx) {
		fmt.Println(n)
		if n == 5 {
			break
		}
	}
}

func ADD(ctx context.Context) int {
	ctx = context.WithValue(ctx, "key", "value")
	ctx = context.WithValue(ctx, "key2", "value2")
	time.Sleep(6 * time.Second)
	go fmt.Println(BDD(ctx))
	select {
	case <-ctx.Done():
		fmt.Println("a time out")
		return -1
	default:
		return 1
	}
}

func BDD(ctx context.Context) int {

	fmt.Println(ctx.Value("key"))
	fmt.Println(ctx.Value("key2"))
	ctx = context.WithValue(ctx, "key3", "value3")

	go fmt.Println(CDD(ctx))
	select {
	case <-ctx.Done():
		fmt.Println("b time out")
		return -2
	default:
		return 2
	}
}

func CDD(ctx context.Context) int {
	fmt.Println(ctx.Value("key3"))
	select {
	case <-ctx.Done():
		fmt.Println("c time out")
		return -3
	default:
		return 3
	}
}

func main2() {
	timeout := time.Second * 5
	ctx, _ := context.WithTimeout(context.Background(), timeout)
	fmt.Println(ADD(ctx))
}

func main() {
	ctx, cancel := context.WithCancel(context.Background())
	go func() {
		time.Sleep(2 * time.Second)
		cancel()
	}()
	fmt.Println(ADD(ctx))
	//select {}
	time.Sleep(50 * time.Second)
}
