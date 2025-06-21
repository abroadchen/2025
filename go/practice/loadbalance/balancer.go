package main

import (
	"container/heap"
	"fmt"
)

type Balancer struct {
	pool Pool
	done chan *Worker
}

func (b *Balancer) start() {
	for _, worker := range b.pool {
		worker.work(b.done)
	}
}

func (b *Balancer) balance(work chan Request) {
	go func() {
		for {
			select {
			case req := <-work:
				b.dispatch(req)
			case w := <-b.done:
				b.completed(w)
			}
		}
	}()
}

func new_balancer(nworker int, work chan Request) *Balancer {
	b := &Balancer{
		make(Pool, nworker), make(chan *Worker, 100),
	}
	for i := 0; i < nworker; i++ {
		b.pool[i] = &Worker{
			make(chan Request, 100), i, 0,
		}
	}
	heap.Init(&b.pool)
	return b
}

func (b *Balancer) dispatch(request Request) {
	w := heap.Pop(&b.pool).(*Worker)
	w.requests <- request
	w.pending++
	heap.Push(&b.pool, w)
}

func (b *Balancer) completed(w *Worker) {
	w.pending--
	heap.Remove(&b.pool, w.index)
	heap.Push(&b.pool, w)
}

func (b *Balancer) print() {
	fmt.Println("\n")
	total_pending := 0
	for _, worker := range b.pool {
		pending := worker.pending
		fmt.Printf("%d pending requests: %d\n", worker.index, pending)
		total_pending += pending
	}
	fmt.Println("| %d", total_pending)
}
