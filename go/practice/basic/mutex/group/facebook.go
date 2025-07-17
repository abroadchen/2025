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
	"github.com/facebookgo/errgroup"
	"time"
)

func main() {
	var g errgroup.Group
	g.Add(3)

	go func() {
		time.Sleep(10 * time.Second)
		fmt.Println("exec #1")
		g.Done()
	}()

	go func() {
		time.Sleep(10 * time.Second)
		fmt.Println("exec #2")
		g.Error(errors.New("failed to exec #2"))
		g.Done()
	}()

	go func() {
		time.Sleep(10 * time.Second)
		fmt.Println("exec #3")
		g.Done()
	}()

	if err := g.Wait(); err == nil {
		fmt.Println("success exec all")
	} else {
		fmt.Println("fail", err)
	}
}
