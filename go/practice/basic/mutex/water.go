/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"context"
	"github.com/marusama/cyclicbarrier"
	"golang.org/x/sync/semaphore"
)

type H20 struct {
	semaH *semaphore.Weighted
	sema0 *semaphore.Weighted
	b     cyclicbarrier.CyclicBarrier
}

func New() *H20 {
	return &H20{
		semaH: semaphore.NewWeighted(2),
		sema0: semaphore.NewWeighted(1),
		b:     cyclicbarrier.New(3),
	}
}

func (m *H20) Hydrogen(releaseHydrogen func()) {
	m.semaH.Acquire(context.Background(), 1)

	releaseHydrogen()
	m.b.Await(context.Background())
	m.semaH.Release(1)
}

func (m *H20) oxygen(releaseOxygen func()) {
	m.sema0.Acquire(context.Background(), 1)
	releaseOxygen()
	m.b.Await(context.Background())
	m.sema0.Release(1)
}
