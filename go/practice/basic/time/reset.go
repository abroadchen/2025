/*
Package time

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package time

import (
	"log"
	"time"
)

func main() {
	ticker := time.NewTicker(time.Second)
	defer ticker.Stop()
	log.Println("create a ticker")

	t := <-ticker.C
	log.Println("the first tick", t.String())

	time.Sleep(time.Second)
	t = <-ticker.C
	log.Println("the second tick", t.String())

	t = <-ticker.C
	log.Println("the third tick", t.String())
}

func correctResetAfterFired() {
	timer := time.NewTimer(time.Second)
	time.Sleep(time.Second)

	b := timer.Stop()
	log.Println("the timer stopped", b)
	if !b {
		<-timer.C
	}
	log.Println("the timer reset")
	timer.Reset(time.Second)
	t := <-timer.C
	log.Println("fired at ", t.String())
}

func wrongReceiveMore() {
	timer := time.NewTimer(time.Second)
	t := <-timer.C
	log.Println("fired at ", t.String())

	t = <-timer.C
	log.Println("receive again at ", t.String())
}
