package test

import (
	"fmt"
	"sync"
	"time"
)

var money int = 0
var mutex sync.Mutex

func add(pint *int, wg *sync.WaitGroup) {
	mutex.Lock()
	for i := 0; i < 100000; i++ {
		*pint++
	}
	mutex.Unlock()
	wg.Done()
}

func main() {
	startime := time.Now()
	var wg sync.WaitGroup
	for i := 0; i < 1000; i++ {
		go add(&money, &wg)
		wg.Add(1)
	}
	wg.Wait()
	fmt.Println("<UNK>", time.Since(startime))
	time.Sleep(10 * time.Second)
}
