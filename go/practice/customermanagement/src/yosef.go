package main

import (
	"container/ring"
	"fmt"
)

//type Player struct {
//	pos   int
//	alive bool
//}

//const (
//	playerCount = 39
//	startpos    = 1
//	deadline    = 3
//)

func Init2() {
	const (
		playerCount = 39
		startpos    = 1
		deadline    = 3
	)

	r := ring.New(playerCount)
	for i := startpos; i <= playerCount; i++ {
		//r.Value = &Player{i, true}
		r.Value = i
		r = r.Next()
	}
	if startpos > 1 {
		r = r.Move(startpos - 1)
	}
	counter := 1
	deadCount := 0

	rpre := r.Prev()
	for deadCount < playerCount {
		//r = r.Next()
		//if r.Value.(*Player).alive {
		//	counter++
		//}
		if counter == deadline {
			//r.Value.(*Player).alive = false
			rpre.Link(rpre.Move(2))
			//fmt.Printf("Player %d 扔进大海\n", r.Value.(*Player).pos)
			fmt.Printf("Player %d 扔进大海\n", r.Value)
			r = rpre.Next()
			deadCount++
			counter = 0
			counter++
		} else {
			rpre = r
			r = r.Next()
			counter++
		}
	}
}
