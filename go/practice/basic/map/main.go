/*
Package _map

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package _map

import (
	"fmt"
	"sync"
)

func main() {
	var m = make(map[int]int, 10)

	go func() {
		for {
			m[1] = 1
		}
	}()

	go func() {
		for {
			_ = m[2]
		}
	}()

	select {}

	var mm sync.Map
	fmt.Println(mm)
}
