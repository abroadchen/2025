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
	"github.com/uw-labs/sync/rungroup"
	"time"
)

func main() {
	ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
	defer cancel()

	g, ctx := rungroup.New(ctx)

	g.Go(func() error {
		return run(ctx, time.Second)
	})
	g.Go(func() error {
		time.Sleep(50 * time.Millisecond)
		return errors.New("component stopped")
	})

	err := g.Wait()
	fmt.Println("err:", err)
}
