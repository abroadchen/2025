/*
Package channel

	@author: June
	@since: 2025/7/17
	@desc:
*/
package channel

import (
	"fmt"
	"github.com/eapache/channels"
	"reflect"
	"sync"
)

func fanIn(chans ...<-chan interface{}) <-chan interface{} {
	out := make(chan interface{})
	go func() {
		var wg sync.WaitGroup
		wg.Add(len(chans))

		for _, c := range chans {
			go func(c <-chan interface{}) {
				for v := range c {
					out <- v
				}
				wg.Done()
			}(c)
		}
		wg.Wait()
		close(out)
	}()
	return out
}

func fanInReflect(chans ...<-chan interface{}) <-chan interface{} {
	out := make(chan interface{})
	go func() {
		defer close(out)
		var cases []reflect.SelectCase
		for _, c := range chans {
			cases = append(cases, reflect.SelectCase{
				Dir:  reflect.SelectRecv,
				Chan: reflect.ValueOf(c),
			})
		}
		for len(cases) > 0 {
			i, v, ok := reflect.Select(cases)
			if !ok {
				cases = append(cases[:i], cases[i+1:]...)
				continue
			}
			out <- v.Interface()
		}
	}()
	return out
}

func fanInRec(chans ...<-chan interface{}) <-chan interface{} {
	switch len(chans) {
	case 0:
		c := make(chan interface{})
		close(c)
		return c
	case 1:
		return chans[0]
	case 2:
		return merge2(chans[0], chans[1])
	default:
		m := len(chans) / 2
		return merge2(fanInRec(chans[:m]...), fanInRec(chans[m:]...))
	}
}

func merge2(a, b <-chan interface{}) <-chan interface{} {
	c := make(chan interface{})

	go func() {
		defer close(c)
		for a != nil || b != nil {
			select {
			case v, ok := <-a:
				if !ok {
					a = nil
					continue
				}
				c <- v
			case v, ok := <-b:
				if !ok {
					b = nil
					continue
				}
				c <- v
			}
		}
	}()
	return c
}

func testPipe() {
	fmt.Println("pipe:")
	a := channels.NewNativeChannel(channels.None)
	b := channels.NewNativeChannel(channels.None)

	channels.Pipe(a, b)

	go func() {
		for i := 0; i < 5; i++ {
			a.In() <- i
		}
		a.Close()
	}()

	for v := range b.Out() {
		fmt.Println(v)
	}
}

func asStream(done <-chan struct{}) <-chan interface{} {
	s := make(chan interface{})
	values := []int{1, 2, 3, 4, 5}
	go func() {
		defer close(s)

		for _, v := range values {
			select {
			case <-done:
				return
			case s <- v:
			}
		}
	}()
	return s
}

func main() {
	fmt.Println("fanIn by goroutine:")
	done := make(chan struct{})
	ch := fanIn(asStream(done), asStream(done), asStream(done))
	for v := range ch {
		fmt.Println(v)
	}
	fmt.Println("fanIn by reflect:")
	ch = fanInReflect(asStream(done), asStream(done), asStream(done))
	for v := range ch {
		fmt.Println(v)
	}
	fmt.Println("fanIn by recursion:")
	ch = fanInRec(asStream(done), asStream(done), asStream(done))
	for v := range ch {
		fmt.Println(v)
	}
}

func testDist() {
	fmt.Println("dist:")
	a := channels.NewNativeChannel(channels.None)
	outputs := []channels.Channel{
		channels.NewNativeChannel(channels.None),
		channels.NewNativeChannel(channels.None),
		channels.NewNativeChannel(channels.None),
		channels.NewNativeChannel(channels.None),
	}
	channels.Distribute(a, outputs[0], outputs[1], outputs[2], outputs[3])

	go func() {
		for i := 0; i < 5; i++ {
			a.In() <- i
		}
		a.Close()
	}()

	for i := 0; i < 6; i++ {
		var v interface{}
		var j int
		select {
		case v = <-outputs[0].Out():
			j = 0
		case v = <-outputs[1].Out():
			j = 1
		case v = <-outputs[2].Out():
			j = 2
		case v = <-outputs[3].Out():
			j = 3
		}
		fmt.Println(v, j)
	}
}

func testTee() {
	fmt.Println("tee:")
	a := channels.NewNativeChannel(channels.None)
	outputs := []channels.Channel{
		channels.NewNativeChannel(channels.None),
		channels.NewNativeChannel(channels.None),
		channels.NewNativeChannel(channels.None),
		channels.NewNativeChannel(channels.None),
	}
	channels.Tee(a, outputs[0], outputs[1], outputs[2], outputs[3])

	go func() {
		for i := 0; i < 5; i++ {
			a.In() <- i
		}
		a.Close()
	}()
}
