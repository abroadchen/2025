package mail

import (
	"container/list"
	"fmt"
)

func main() {
	myq := list.New()
	for i := 0; i < 10; i++ {
		myq.PushBack(i)
	}
	for myq.Len() != 0 {
		fmt.Println(myq.Front())
		myq.Remove(myq.Front())
	}

	mystack := list.New()
	for i := 0; i < 10; i++ {
		mystack.PushBack(i)
		fmt.Println(i)
	}
	for mystack.Len() != 0 {
		fmt.Println(mystack.Back())
		mystack.Remove(mystack.Back())
	}
}
