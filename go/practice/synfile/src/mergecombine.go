package main

import (
	"fmt"
	"math/rand"
	"strconv"
	"time"
)

func Pproducer(ch chan<- string, name string) {
	for i := 0; i < 5; i++ {
		time.Sleep(time.Second)
		n := rand.Intn(100) + 1
		fmt.Printf("channel ->", name, n)
		ch <- strconv.Itoa(n)
		//ch<-n
	}
	close(ch)
}

func Cconsumer(ch <-chan string) {
	for n := range ch {
		fmt.Println("<-", n)
	}
	fmt.Println("")
}

func FanIN(chall0, chall1, chall2, chall3, chall4 <-chan string, chc chan<- string) {
	var n string
	for {
		select {
		case n = <-chall0:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall1:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall2:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall3:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall4:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		}
	}
	fmt.Println("func FanIN()")
}

//func FanIN(cha, chb <-chan int, chc chan<- int) {
//	var n int
//	isok1 := false
//	isok2 := false
//	for {
//		select {
//		case n = <-cha:
//			if n == 0 {
//				isok1 = true
//				break
//			}
//			chc <- n
//		case n = <-chb:
//			if n == 0 {
//				isok2 = true
//				break
//			}
//			chc <- n
//		}
//		if isok1 && isok2 {
//			break
//		}
//	}
//}

func FanOUT(cha <-chan int, chb, chc chan<- int) {
	for n := range cha {
		if n < 50 {
			chb <- n
		} else {
			chc <- n
		}
	}
}

func main() {
	chall0 := make(chan string)
	chall1 := make(chan string)
	chall2 := make(chan string)
	chall3 := make(chan string)
	chall4 := make(chan string)
	chc := make(chan string)
	go Pproducer(chall0, "A")
	go Pproducer(chall1, "B")
	go Pproducer(chall2, "C")
	go Pproducer(chall3, "D")
	go Pproducer(chall4, "E")
	go Cconsumer(chc)
	FanIN(chall0, chall1, chall2, chall3, chall4, chc)

	//cha := make(chan int)
	//chb := make(chan int)
	//chc := make(chan int, 5)
	//go Pproducer(cha, "A")
	//go Pproducer(chb, "B")
	//
	//chx := make(chan int)
	//chy := make(chan int)
	//
	//go Cconsumer(chx, "X")
	//go Cconsumer(chy, "Y")
	//go FanOUT(chc, chx, chy)
	//time.Sleep(time.Millisecond * 10)
	//FanIN(cha, chb, chc)

}
