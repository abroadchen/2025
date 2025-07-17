/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

type Mutex5 struct {
	ch chan struct{}
}

func NewMutex5() *Mutex5 {
	mu := &Mutex5{ch: make(chan struct{}, 1)}
	mu.ch <- struct{}{}
	return mu
}

func (m *Mutex5) Lock() {
	<-m.ch
}

func (m *Mutex5) Unlock() {
	select {
	case m.ch <- struct{}{}:
	default:
		panic("unlock of unlocked mutex")
	}
}

func (m *Mutex5) TryLock() bool {
	select {
	case <-m.ch:
		return true
	default:
	}
	return false
}

func (m *Mutex5) IsLocked() bool {
	return len(m.ch) == 0
}
