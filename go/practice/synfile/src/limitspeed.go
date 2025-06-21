package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type batch []string

func create(n int) *batch {
	documents := make(batch, 0)
	for i := 0; i < n; i++ {
		documents = append(documents, fmt.Sprintf("document-%d", 100+rand.Intn(200)))
	}
	return &documents
}

func (b *batch) process(maxRate int) {
	fmt.Println("Processing batch", &b)
	var wg sync.WaitGroup
	wg.Add(len(*b))
	rateLimiter := make(chan bool, maxRate)
	for _, elem := range *b {
		rateLimiter <- true
		go processElem(elem, &wg, rateLimiter)
	}
	wg.Wait()
}

func processElem(elem string, wg *sync.WaitGroup, rl chan bool) {
	defer wg.Done()
	fmt.Println("Processing element", elem)
	time.Sleep(time.Duration(500+rand.Intn(500)) * time.Millisecond)
	<-rl
}

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	for i := 0; i < 11; i++ {
		fmt.Println("\nLimiting max rate to", i, "\n")
		create(10).process(i)
	}
}
