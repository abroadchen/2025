/*
Package mutex

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package mutex

import (
	"fmt"
	"sync"
	"sync/atomic"
	"time"
	"unsafe"
)

type RWMutex struct {
	sync.RWMutex
}

type m struct {
	w           sync.Mutex
	writerSem   uint32
	readerSem   uint32
	readerCount int32
	readerWait  int32
}

func (rw *RWMutex) ReaderCount() int {
	v := (*m)(unsafe.Pointer(&rw.RWMutex))
	c := int(v.readerCount)
	if c < 0 {
		c = int(v.readerWait)
	}
	return c
}

func (rw *RWMutex) WriterCount() int {
	v := atomic.LoadInt32((*int32)(unsafe.Pointer(&rw.RWMutex)))
	v = v >> mutexWaiterShift
	v = v + (v & mutexLocked)
	return int(v)
}

func main() {
	var mu RWMutex

	for i := 0; i < 10; i++ {
		go func() {
			mu.RLock()
			time.Sleep(time.Millisecond)
			mu.RUnlock()
		}()
	}

	for i := 0; i < 10; i++ {
		go func() {
			mu.RLock()
			time.Sleep(time.Millisecond)
			mu.RUnlock()
		}()
	}

	fmt.Println("Reader Count:", mu.ReaderCount())
	fmt.Println("Writer Count:", mu.WriterCount())
}
