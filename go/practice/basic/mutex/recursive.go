/*
Package mutex

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package mutex

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	var mu sync.RWMutex
	var wg sync.WaitGroup
	wg.Add(2)

	go func() {
		defer wg.Done()
		time.Sleep(1 * time.Second)
		mu.Lock()
		fmt.Println("lock")
		time.Sleep(1 * time.Second)
		mu.Unlock()
		fmt.Println("unlock")
	}()

	go func() {
		defer wg.Done()
		factorial(&mu, 4)
	}()

	time.Sleep(1 * time.Second)
	wg.Wait()
}

func factorial(mu *sync.RWMutex, n int) int {
	if n < 1 {
		return 0
	}
	fmt.Printf("RLock")
	mu.RLock()
	defer func() {
		fmt.Printf("RUnlock")
		mu.RUnlock()
	}()
	time.Sleep(time.Duration(n) * time.Second)
	return factorial(mu, n-1) * n
}
