package stack

import "my-distributed-project/datastruct/queue"

type Stack struct {
	Ql queue.Queue
	Qr queue.Queue
}

func (q *Stack) Push(item string) {
	if len(q.Ql.Items) == 0 {
		q.Ql.Enqueue(item)
	} else {
		for len(q.Ql.Items) != 0 {
			q.Qr.Enqueue(q.Ql.Dequeue())
		}
		q.Ql.Enqueue(item)
	}
}
func (q *Stack) Pop() string {
	if len(q.Ql.Items) == 1 {
		return q.Ql.Dequeue()
	} else if len(q.Ql.Items) == 0 {
		if len(q.Qr.Items) == 0 {
			panic("empty")
		} else if len(q.Qr.Items) == 1 {
			return q.Qr.Dequeue()
		} else {
			for len(q.Qr.Items) != 0 {
				q.Ql.Enqueue(q.Qr.Dequeue())
			}
			for len(q.Ql.Items) > 1 {
				q.Qr.Enqueue(q.Ql.Dequeue())
			}
			return q.Ql.Dequeue()
		}
	} else {
		for len(q.Ql.Items) != 0 {
			q.Qr.Enqueue(q.Ql.Dequeue())
		}
		return q.Ql.Dequeue()
	}
	return ""
}
