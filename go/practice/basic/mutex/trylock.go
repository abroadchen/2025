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
	"unsafe"
)

type Mutex3 struct {
	mu sync.Mutex
}

func (m *Mutex3) Lock() {
	m.mu.Lock()
}
func (m *Mutex3) Unlock() {
	m.mu.Unlock()
}
func (m *Mutex3) TryLock() bool {
	return atomic.CompareAndSwapUint32((*uint32)(unsafe.Pointer(&m.mu)), 0, mutexLocked)
}

func (m *Mutex3) IsLocked() bool {
	return atomic.LoadUint32((*uint32)(unsafe.Pointer(&m.mu))) == mutexLocked
}
