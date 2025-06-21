package main

import (
	"fmt"
	"math/rand"
	"time"
)

var (
	Web   = fakeSearch("web")
	Image = fakeSearch("image")
	Map   = fakeSearch("map")

	Vedio    = fakeSearch("vedio")
	BigImage = fakeSearch("BigImage")
	Edu      = fakeSearch("edu")
)

type Result string
type SearchX func(query string) Result

func fakeSearch(kind string) SearchX {
	return func(query string) Result {
		time.Sleep(time.Duration(rand.Intn(3)) * time.Second)
		return Result(fmt.Sprintf("%s result for %s\n", kind, query))
	}
}

func Google(query string) (results []Result) {
	//res := make([]Result, 3, 3)
	//res = append(res, Web(query))
	//res = append(res, Image(query))
	//res = append(res, Map(query))
	//return res
	res := make(chan Result)
	go func() {
		//res <- Web(query)
		res <- First(query, Web, Vedio)
	}()
	go func() {
		//res <- Image(query)
		res <- First(query, Image, BigImage)
	}()
	go func() {
		//res <- Map(query)
		res <- First(query, Map, Edu)
	}()
	timeout := time.After(3 * time.Second)
	for i := 0; i < 3; i++ {
		//result := <-res
		//results = append(results, result)
		select {
		case r := <-res:
			results = append(results, r)
		case <-timeout:
			fmt.Println("Timed out")
			return
		}
	}
	return results
}

func First(query string, replices ...SearchX) Result {
	c := make(chan Result)
	searchReplices := func(i int) {
		c <- replices[i](query)
	}
	for i := range replices {
		go searchReplices(i)
	}
	return <-c
}

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	starttime := time.Now()
	//res := Google("golang")
	res := First("golang", fakeSearch("replica 1"), fakeSearch("replica 2"))
	fmt.Println(res)
	fmt.Println(time.Since(starttime))
}
