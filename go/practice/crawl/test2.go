/*
Package crawl

	@author: chen
	@since: 2025/7/15
	@desc: 线程安全的map结构解决并发去重
*/
package crawl

import (
	"fmt"

	"github.com/dokidokikoi/go-cmap"
	"time"
)

func main() {
	number := 30
	concurrency := number / 2
	cm, _ := cmap.NewConcurrentMap(concurrency, nil)

	go func() {
		ok, err := cm.Put("hello", "world")
		fmt.Println(ok, err)
	}()
	time.Sleep(1 * time.Second)
	actualElement := cm.Get("hello")
	fmt.Println(actualElement)
}
