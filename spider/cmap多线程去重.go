package spider

import (
	"fmt"
	"time"
)

func main() {
	number := 30
	concurrency := number / 2
	cm, _ := cmap.NewConcurrentMap(concurrency, nil)
	go func() {
		ok, err := cm.Put("key", "value")
		fmt.Println(ok, err)
	}()
	time.Sleep(1 * time.Second)
	actualElement := cm.Get("key")
	fmt.Println(actualElement)
}
