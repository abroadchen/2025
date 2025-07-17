/*
Package time

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package time

import (
	"fmt"
	"log"
	"runtime"
	"time"
)

func main() {
	runtime.GC()
	mem := runtime.MemStats{}
	runtime.ReadMemStats(&mem)
	fmt.Println("before:", mem.HeapInuse)
	for i := 0; i < 10; i++ {
		task()
	}
	runtime.GC()
	runtime.ReadMemStats(&mem)
	fmt.Println("after:", mem.HeapInuse)

	time.Sleep(1 * time.Second)
	runtime.GC()
	runtime.ReadMemStats(&mem)
	fmt.Println("fired:", mem.HeapInuse)
}

func task() {
	select {
	case <-time.After(1 * time.Second):
		fmt.Println("timeout")
		return
	default:
	}
}

func main2() {
	timer := time.AfterFunc(time.Second, func() {
		fmt.Println("fired")
	})
	go func() {
		t := <-timer.C
		log.Printf("fired at %v", t)
	}()
	time.Sleep(2 * time.Second)
}
