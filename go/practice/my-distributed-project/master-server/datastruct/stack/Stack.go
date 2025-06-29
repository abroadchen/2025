package stack

import "my-distributed-project/master-server/datastruct/queue"

type Stack struct {
	Ql queue.Queue
	Qr queue.Queue
}

func (q *Stack) Push(item string) {
	if len(q.Ql.Items) == 0 {
		q.Ql.Enqueue(item) //为空直接入队
	} else {
		for len(q.Ql.Items) != 0 { //不为空转移到右边
			q.Qr.Enqueue(q.Ql.Dequeue())
		}
		q.Ql.Enqueue(item) //为空再次入队
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

func main() {
	q1 := queue.Queue(make(chan string, 100))
}
