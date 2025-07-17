/*
Package channel

	@author: June
	@since: 2025/7/17
	@desc:
*/
package channel

func fanOut2(ch <-chan interface{}, out []chan interface{}) {
	go func() {
		defer func() {
			for i := 0; i < len(out); i++ {
				close(out[i])
			}
		}()

		var i = 0
		var n = len(out)
		for v := range ch {
			v := v
			out[i] <- v
			i = (i + 1) % n
		}
	}()
}
