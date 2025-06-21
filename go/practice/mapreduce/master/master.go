package master

import "fmt"

var (
	MapChanIn      chan MapInput
	MapChanOut     chan string
	ReduceChanIn   chan string
	ReduceChanOut  chan string
	CombineChanIn  chan string
	CombineChanOut chan []Item
)

func Handle(inputArr []string, fileDir string) []Item {
	fmt.Println("Handle called!")
	const (
		mapperNumber int = 5
		reduceNumber int = 2
	)
	MapChanIn = make(chan MapInput)
	MapChanOut = make(chan string)
	ReduceChanIn = make(chan string)
	ReduceChanOut = make(chan string)
	CombineChanIn = make(chan string)
	CombineChanOut = make(chan []Item)

	reduceJobNum := len(inputArr)
	combineJobNum := reduceJobNum
	go Combiner()
	for i := 1; i <= reduceNumber; i++ {
		go reducer(i, fileDir)
	}
	for i := 1; i <= mapperNumber; i++ {
		go mapper(i, fileDir)
	}
	go func() {
		for i, v := range inputArr {
			MapChanIn <- MapInput{v, i + 1}
		}
		close(MapChanIn)
	}()
	var res []Item
outer:
	for {
		select {
		case v := <-MapChanOut:
			go func() {
				ReduceChanIn <- v
				reduceJobNum--
				if reduceJobNum <= 0 {
					close(ReduceChanIn)
				}
			}()
		case v := <-ReduceChanOut:
			go func() {
				CombineChanIn <- v
				combineJobNum--
				if combineJobNum <= 0 {
					close(CombineChanIn)
				}
			}()
		case v := <-CombineChanOut:
			res = v
			break outer
		}
	}
	close(MapChanOut)
	close(ReduceChanOut)
	close(CombineChanOut)
	return res
}
