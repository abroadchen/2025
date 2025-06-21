package main

import "fmt"

func is_it(str string) bool {
	ch := make(chan byte)
	length := len(str)
	go func() {
		for i := 0; i < length; i++ {
			ch <- str[i]
		}
	}()
	for i := length - 1; i >= 0; i-- {
		if <-ch != str[i] {
			return false
		}
	}
	return true
}

func main() {
	fmt.Println(is_it("abc"))
	fmt.Println(is_it("abcba"))
}
