package queue

type Queue struct {
	Items chan string
}

func (q *Queue) Enqueue(items string) {
	q.Items <- items
}

func (q *Queue) Dequeue() string {
	return <-q.Items
}
