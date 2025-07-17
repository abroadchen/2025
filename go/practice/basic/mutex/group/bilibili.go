/*
Package group

	@author: June
	@since: 2025/7/17
	@desc:
*/
package group

import (
	"context"
	"fmt"
	"github.com/go-kratos/kratos/pkg/sync/errgroup"
	"sync/atomic"
	"time"
)

func main() {
	var g errgroup.Group
	g.GOMAXPROCS(10)

	var count int64
	g.Go(func(ctx context.Context) error {
		time.Sleep(time.Second)
		return nil
	})

	total := 10000

	for i := 0; i < total; i++ {
		go func(i int) {
			g.Go(func(ctx context.Context) error {
				atomic.AddInt64(&count, 1)
				return nil
			})
			fmt.Println(i, "is ok")
		}(i)
	}

	if err := g.Wait(); err != nil {
		panic(err)
	}

	got := atomic.LoadInt64(&count)
	if got != int64(total) {
		fmt.Sprintf("expect %d, but got %d", total, got)
	} else {
		fmt.Println("all ok", got, total)
	}

	time.Sleep(100 * time.Second)
}
