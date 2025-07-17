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
	hunch "github.com/aaronjan/Hunch"
	"time"
)

func main() {
	ctx := context.Background()
	r, err := hunch.All(
		ctx,
		func(ctx context.Context) (interface{}, error) {
			time.Sleep(300 * time.Millisecond)
			return 1, nil
		},
		func(ctx context.Context) (interface{}, error) {
			time.Sleep(200 * time.Millisecond)
			return 0, errors.New("#2 failed")
		},
		func(ctx context.Context) (interface{}, error) {
			time.Sleep(100 * time.Millisecond)
			return 3, nil
		})

	fmt.Println(r, err)
}
