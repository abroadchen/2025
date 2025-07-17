/*
Package ext

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package main

import (
	"context"
	"github.com/marusama/cyclicbarrier"
	"log"
	"math/rand"
	"sync"
	"time"
)

func main() {
	cnt := 0
	b := cyclicbarrier.NewWithAction(10, func() error {
		cnt++
		return nil
	})

	wg := sync.WaitGroup{}
	wg.Add(10)

	for i := 0; i < 10; i++ {
		i := i
		go func() {
			defer wg.Done()
			for j := 0; j < 5; j++ {
				time.Sleep(time.Duration(rand.Intn(10)) * time.Second)
				log.Printf("goroutine %d waits", i)
				err := b.Await(context.TODO())
				if err != nil {
					panic(err)
				}
			}
		}()
	}
	wg.Wait()
}
