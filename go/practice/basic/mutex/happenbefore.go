/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"sync"
	"sync/atomic"
)

var a uint64
var mu sync.Mutex

func foo() {
	if a == 1 {
		return
	}
	mu.Lock()
	if a == 0 {
		a = 1
	}
	mu.Unlock()
}

func fooByAtomic() {
	if atomic.LoadUint64(&a) == 1 {
		return
	}
	mu.Lock()
	if a == 0 {
		atomic.StoreUint64(&a, 1)
	}
	mu.Unlock()
}

func fooByMoreScope() {
	mu.Lock()
	defer mu.Unlock()

	if a == 1 {
		return
	}
	a = 1
}
