/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import "time"

type Mutex7 struct {
	ch chan struct{}
}

func NewMutex7() *Mutex7 {
	mu := &Mutex7{make(chan struct{}, 1)}
	mu.ch <- struct{}{}
	return mu
}

func (m *Mutex7) Lock() {
	<-m.ch
}

func (m *Mutex7) Unlock() {
	select {
	case m.ch <- struct{}{}:
	default:
		panic("unlock of unlocked mutex")
	}
}

func (m *Mutex7) TryLock(timeout time.Duration) bool {
	timer := time.NewTimer(timeout)
	select {
	case <-m.ch:
		timer.Stop()
		return true
	case <-time.After(timeout):
	}
	return false
}

func (m *Mutex7) IsLocked() bool {
	return len(m.ch) == 0
}
