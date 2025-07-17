/*
Package future

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package future

import (
	"context"
	"fmt"
	"github.com/reugn/async"
	"time"
)

func main() {
	p := async.NewPromise[bool]()
	go func() {
		time.Sleep(1 * time.Second)
		p.Success(true)
	}()
	v, e := p.Future().Get(context.Background())
	fmt.Println("v:", v, "e:", e)

	p1 := async.NewPromise[int]()
	p2 := async.NewPromise[int]()
	p3 := async.NewPromise[int]()
	go func() {
		time.Sleep(1 * time.Second)
		p1.Success(1)
		time.Sleep(1 * time.Second)
		p2.Success(2)
		time.Sleep(1 * time.Second)
		p3.Success(3)
	}()
}
