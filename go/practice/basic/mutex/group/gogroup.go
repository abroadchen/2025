/*
Package group

	@author: June
	@since: 2025/7/17
	@desc:
*/
package group

import (
	"context"
	"errors"
	"fmt"
	"time"
)

import (
	"github.com/uw-labs/sync/gogroup"
)

func main() {
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	g, ctx := gogroup.New(ctx)

	g.Go(func() error {
		return run(ctx, time.Second)
	})
	g.Go(func() error {
		time.Sleep(10 * time.Second)
		return errors.New("component stopped")
	})

	fmt.Println(g.Wait())
}

func run(ctx context.Context, d time.Duration) error {
	select {
	case <-ctx.Done():
		return ctx.Err()
	case <-time.After(d):
		return nil
	}
}
