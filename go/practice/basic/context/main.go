/*
Package context

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package context

import (
	"context"
	"fmt"
	"time"
)

func main1() {
	ctx := context.Background()

	ctx1, c1 := context.WithCancel(ctx)
	go func() {
		fmt.Println("g1 start")
		<-ctx1.Done()
		fmt.Println("g1 end, err:", ctx1.Err())
	}()

	ctx2, c2 := context.WithCancel(ctx1)
	go func() {
		fmt.Println("g2 start")
		<-ctx2.Done()
		fmt.Println("g2 end, err:", ctx2.Err())
	}()

	ctx3, c3 := context.WithCancel(ctx2)
	go func() {
		fmt.Println("g3 start")
		<-ctx3.Done()
		fmt.Println("g3 end, err:", ctx3.Err())
	}()

	time.Sleep(1e9)
	c1()
	time.Sleep(5 * time.Second)
	c2()
	time.Sleep(5 * time.Second)
	c3()
}

func main2() {
	ctx := context.Background()

	ctx1, c1 := context.WithCancel(ctx)
	go func() {
		fmt.Println("g1 start")
		<-ctx1.Done()
		fmt.Println("g1 end, err:", ctx1.Err())
	}()

	ctx2 := context.WithValue(ctx1, "key", "value")
	go func() {
		fmt.Println("g2 start")
		<-ctx2.Done()
		fmt.Println("g2 end, err:", ctx2.Err())
	}()

	ctx3, c3 := context.WithCancel(ctx2)
	go func() {
		fmt.Println("g3 start")
		<-ctx3.Done()
		fmt.Println("g3 end, err:", ctx3.Err())
	}()

	time.Sleep(1e9)
	c1()
	time.Sleep(5 * time.Second)
	c3()
}

func main3() {
	ctx := context.Background()
	ctx = context.TODO()
	ctx = context.WithValue(ctx, "key", "value")
	ctx = context.WithValue(ctx, "key2", "value2")
	ctx = context.WithValue(ctx, "key3", "value3")
	ctx = context.WithValue(ctx, "key4", "value4")
	fmt.Println(ctx.Value("key"))
}

func main() {
	ctx1, c1 := context.WithCancel(context.Background())
	go func() {
		fmt.Println("g1 start")
		<-ctx1.Done()
		fmt.Println("g1 end, err:", ctx1.Err())
	}()

	ctx2, c2 := context.WithDeadline(ctx1, time.Now().Add(5*time.Second))
	go func() {
		fmt.Println("g2 start")
		<-ctx2.Done()
		fmt.Println("g2 end, err:", ctx2.Err())
	}()

	time.Sleep(time.Second)
	c1()
	time.Sleep(5 * time.Second)
	c2()
}
