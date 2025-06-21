package master

import (
	"bufio"
	"container/heap"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Item struct {
	key string
	val int
}

type PriorityQueue []*Item

func (pq PriorityQueue) Len() int { return len(pq) }
func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].val > pq[j].val
}
func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
}
func (pq *PriorityQueue) Push(x interface{}) {
	item := x.(*Item)
	*pq = append(*pq, item)
}
func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	*pq = old[0 : n-1]
	return item
}
func Combiner() {
	mp := make(map[string]int)
	for {
		val, ok := <-CombineChanIn
		if !ok {
			break
		}
		fmt.Println("Combiner")
		file, err := os.Open(val)
		if err != nil {
			errMsg := fmt.Sprintf("open file err:%s", val)
			fmt.Println(errMsg)
			continue
		}
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			str := scanner.Text()
			arr := strings.Split(str, " ")
			if len(arr) != 2 {
				errMsg := fmt.Sprintf("readfile %s err in combine %s", val, str)
				fmt.Println(errMsg)
				continue
			}
			v, err := strconv.Atoi(arr[1])
			if err != nil {
				errMsg := fmt.Sprintf("strconv %s err in combine %s", val, str)
				fmt.Println(errMsg)
				continue
			}
			mp[arr[0]] += v
		}
		file.Close()
	}
	pq := make(PriorityQueue, 0)
	heap.Init(&pq)
	for k, v := range mp {
		node := &Item{k, v}
		heap.Push(&pq, node)
	}
	res := []Item{}
	for i := 0; i < 10 && pq.Len() > 0; i++ {
		node := heap.Pop(&pq).(*Item)
		res = append(res, *node)
	}
	CombineChanOut <- res
}
