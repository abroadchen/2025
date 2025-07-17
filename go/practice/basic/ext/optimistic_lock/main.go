/*
Package optimistic_lock

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package optimistic_lock

import (
	"fmt"
	"github.com/petermattis/goid"
	"runtime"
	"strconv"
	"strings"
	"sync"
	"sync/atomic"
)

type RecursiveMutex struct {
	sync.Mutex
	owner     int64
	recursion int32
}

func (m *RecursiveMutex) Lock() {
	gid := goid.Get()
	if atomic.LoadInt64(&m.owner) == gid {
		m.recursion++
		return
	}
	m.Mutex.Lock()
	atomic.StoreInt64(&m.owner, gid)
	m.recursion = 1
}

func (m *RecursiveMutex) Unlock() {
	gid := goid.Get()
	if atomic.LoadInt64(&m.owner) != gid {
		fmt.Sprintf("wrong the owner (%d): %d", m.owner, gid)
	}
	m.recursion--
	if m.recursion != 0 {
		return
	}
	atomic.StoreInt64(&m.owner, -1)
	m.Mutex.Unlock()
}

func GoID() int {
	var buf [64]byte
	n := runtime.Stack(buf[:], false)
	idField := strings.Fields(strings.TrimPrefix(string(buf[:n]), "goroutine "))[0]
	id, err := strconv.Atoi(idField)
	if err != nil {
		fmt.Sprintf("cannot get goroutine id: %v", err)
	}
	return id
}

func main() {
	fmt.Println(GoID())
	var wg sync.WaitGroup
	for i := 0; i < 10; i++ {
		i := i
		wg.Add(1)
		go func() {
			defer wg.Done()
			fmt.Println(i, GoID())
		}()
	}
	wg.Wait()
}

//func main() {
//	var sv = &syncValue{
//		l: async.NewOptimisticLock(),
//	}
//	var wg sync.WaitGroup
//	wg.Add(1)
//
//	for i := 0; i < 10; i++ {
//		go func() {
//			for i := 0; i < 100; i++ {
//				fmt.Println("read:", sv.read())
//			}
//		}()
//		wg.Done()
//	}
//
//	go func() {
//		for i := 0; i < 100; i++ {
//			sv.incr()
//			time.Sleep(1 * time.Second)
//		}
//		wg.Done()
//	}()
//	wg.Wait()
//}

//type syncValue struct {
//	v int
//	l *async.OptimisticLock
//}
//
//func (sv *syncValue) read() int {
//	var v int
//	ok := false
//	for !ok {
//		stamp := sv.l.OptLock()
//		v = sv.v
//		ok = sv.l.OptUnlock(stamp)
//	}
//	return v
//}
//
//func (sv *syncValue) incr() {
//	sv.l.Lock()
//	sv.v++
//	sv.l.Unlock()
//}
