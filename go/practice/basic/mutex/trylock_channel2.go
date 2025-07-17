/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

type Mutex6 struct {
	ch chan struct{}
}

func NewMutex6() *Mutex6 {
	mu := &Mutex6{make(chan struct{}, 1)}
	return mu
}

func (m *Mutex6) Lock() {
	m.ch <- struct{}{}
}

func (m *Mutex6) Unlock() {
	select {
	case <-m.ch:
	default:
		panic("unlock of unlocked mutex")
	}
}

func (m *Mutex6) TryLock() bool {
	select {
	case m.ch <- struct{}{}:
		return true
	default:
	}
	return false
}

func (m *Mutex6) IsLocked() bool {
	return len(m.ch) == 1
}
