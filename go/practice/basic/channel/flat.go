/*
Package channel

	@author: June
	@since: 2025/7/17
	@desc:
*/
package channel

import "fmt"

func orDone(done <-chan struct{}, c <-chan interface{}) <-chan interface{} {
	valStream := make(chan interface{})
	go func() {
		defer close(valStream)
		for {
			select {
			case <-done:
				return
			case v, ok := <-c:
				if ok == false {
					return
				}
				select {
				case valStream <- v:
				case <-done:
				}
			}
		}
	}()
	return valStream
}

/*
flat

	  @Description:
		chanStream <-chan <-chan interface{} 表示：
		chanStream 是一个只读通道（<-chan），用于接收数据。
		它接收的数据类型是另一个只读通道（<-chan interface{}），即通道中传递的是“通道本身”。
	  @param done
	  @param chanStream
	  @return <-chan
*/
func flat(done <-chan struct{}, chanStream <-chan <-chan interface{}) <-chan interface{} {
	valStream := make(chan interface{})
	go func() {
		defer close(valStream)
		for {
			var stream <-chan interface{}
			select {
			case maybeStream, ok := <-chanStream:
				if ok == false {
					return
				}
				stream = maybeStream
			case <-done:
				return
			}
			for val := range orDone(done, stream) {
				select {
				case valStream <- val:
				case <-done:
				}
			}
		}
	}()
	return valStream
}

func main() {
	genVals := func() <-chan <-chan interface{} {
		chanStream := make(chan (<-chan interface{}))
		go func() {
			defer close(chanStream)
			for i := 0; i < 10; i++ {
				stream := make(chan interface{}, 1)
				stream <- i
				close(stream)
				chanStream <- stream
			}
		}()
		return chanStream
	}

	for v := range flat(nil, genVals()) {
		fmt.Println(v)
	}
}
