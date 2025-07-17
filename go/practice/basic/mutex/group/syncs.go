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
	"github.com/go-pkgz/syncs"
	"sync/atomic"
	"time"
)

func main() {
	ewg := syncs.NewErrSizedGroup(10, syncs.Preemptive)
	var c uint32

	for i := 0; i < 1000; i++ {
		i := i
		ewg.Go(func() error {
			time.Sleep(time.Microsecond * 10)
			atomic.AddUint32(&c, 1)
			if i == 100 {
				errors.New("err1")
			}
			if i == 200 {
				errors.New("err2")
			}
			return nil
		})
	}

	if err := ewg.Wait(); err != nil {
		fmt.Println(err)
	}
	fmt.Printf("%v\n", c)
}
