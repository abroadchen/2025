package mail

import (
	"bufio"
	"fmt"
	"os"
	"sync"
	"sync/atomic"
	"time"
)

var money int64 = 0
var mutex sync.Mutex

func add(pint *int64, wg *sync.WaitGroup) {
	mutex.Lock()
	for i := 0; i < 100000; i++ {
		//*pint++
		atomic.AddInt64(pint, 1)
	}
	mutex.Unlock()
	wg.Done()
}

func main() {
	startime := time.Now()
	var wg sync.WaitGroup
	for i := 0; i < 1000; i++ {
		go add(&money, &wg)
		wg.Add(1)
	}
	//time.Sleep(time.Second * 10)
	wg.Wait()
	fmt.Println(time.Since(startime))
	fmt.Println(money)
}

type SafeFile struct {
	mutex    *sync.Mutex
	savefile *os.File
}

func main1() {
	var sf = new(SafeFile)
	sf.mutex = new(sync.Mutex)
	sf.savefile, _ = os.Create("email.txt")
	defer sf.savefile.Close()
	save := bufio.NewWriter(sf.savefile)
	for i := 0; i < 10; i++ {
		go fmt.Fprintf(save, "")
	}
	time.Sleep(time.Second * 10)
	save.Flush()
}
