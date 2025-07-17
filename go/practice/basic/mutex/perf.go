/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import "testing"

func BenchmarkChan_With2Cases(b *testing.B) {
	ch := make(chan struct{}, 1000)
	done := make(chan struct{})

	go func() {
		for {
			select {
			case <-done:
				return
			case <-ch:
			}
		}
	}()

	for i := 0; i < b.N; i++ {
		ch <- struct{}{}
	}
	close(done)
}
