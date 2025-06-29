package testMSG

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan string)
	go func() {
		time.Sleep(5 * time.Second)
		ch <- "<UNK>"
	}()
	select {
	case msg := <-ch:
		fmt.Println(msg)
	case <-time.After(1 * time.Second):
		fmt.Println("timeout")
		forever <- true
		break
	}
}
