package mail

import (
	"strconv"
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup
	for i := 1; i <= 8; i++ {
		url := "" + strconv.Itoa(i) + ".shtml"
		wg.Add(1)
		go GetMail2(url, &wg)
	}
	wg.Wait()

	time.Sleep(time.Second * 1)
}
