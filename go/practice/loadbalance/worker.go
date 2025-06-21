package main

type Worker struct {
	requests chan Request
	pending  int
	index    int
}

func (w *Worker) work(done chan *Worker) {
	go func() {
		for {
			req := <-w.requests
			req.c <- req.fn()
			done <- w
		}
	}()
}
