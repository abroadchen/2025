package main

import (
	"fmt"
	"io"
	"math/rand"
	"time"
)
import crand "crypto/rand"

func randx() chan int {
	ch := make(chan int)
	go func() {
		for {
			select {
			case ch <- 0:
			case ch <- 1:
			case ch <- 2:
			}
		}
	}()
	return ch
}

func srange() chan int {
	var ch chan int = make(chan int)
	go func() {
		for i := 0; ; i++ {
			ch <- i
		}
	}()
	return ch
}

func Getpassword() chan string {
	var ch chan string = make(chan string)
	go func() {
		var chars = []byte("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz0123456789")
		var Minlength, Maxlength = 6, 16
		rand.Seed(time.Now().Unix())
		for {
			var length = rand.Intn(Maxlength-Minlength+1) + Minlength
			newPassword := make([]byte, length)
			randomData := make([]byte, length+length/4)
			clen := byte(len(chars))
			maxrb := byte(256 - (256 % len(chars)))
			i := 0
			for {
				if _, err := io.ReadFull(crand.Reader, randomData); err != nil {
					panic(err)
				}
				isok := false
				for _, c := range randomData {
					if c >= maxrb {
						continue
					}
					newPassword[i] = chars[c%clen]
					i++
					if i == length {
						ch <- string(newPassword)
						isok = true
						break
					}
				}
				if isok {
					break
				}
			}
		}
	}()

	return ch
}

func main() {
	//maker := rand()
	//for i := 0; i < 10; i++ {
	//	fmt.Println(<-maker)
	//}

	passmaker := Getpassword()
	fmt.Println(<-passmaker)
}
