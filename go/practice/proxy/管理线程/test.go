package 管理线程

import (
	"context"
	"fmt"
	"time"
)

func Proc(ctx context.Context, n int) {
	for {
		select {
		case <-ctx.Done():
			fmt.Println(ctx, n, "线程结束")
			return
		default:
			fmt.Println("Proc-%d\n", n)
		}
	}
}

func main() {
	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)
	go Proc(ctx, 1)
	go Proc(ctx, 2)
	go Proc(ctx, 3)
	go Proc(ctx, 4)

	time.Sleep(time.Second)
	cancel()
	time.Sleep(time.Second * 10)
}
