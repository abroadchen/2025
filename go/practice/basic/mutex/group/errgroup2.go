/*
Package group

	@author: June
	@since: 2025/7/17
	@desc:
*/
package group

import (
	"errors"
	"fmt"
	"golang.org/x/sync/errgroup"
	"time"
)

func main() {
	var g errgroup.Group
	var result = make([]error, 3)

	g.Go(func() error {
		time.Sleep(5 * time.Second)
		fmt.Println("exec #1")
		result[0] = nil
		return nil
	})

	g.Go(func() error {
		time.Sleep(10 * time.Second)
		fmt.Println("exec #2")

		result[1] = errors.New("failed to exec #2")
		return result[1]
	})

	g.Go(func() error {
		time.Sleep(15 * time.Second)
		fmt.Println("exec #3")
		result[2] = nil
		return nil
	})

	if err := g.Wait(); err == nil {
		fmt.Printf("success exec all result: %v", result)
	} else {
		fmt.Printf("failed: %v", result)
	}
}
