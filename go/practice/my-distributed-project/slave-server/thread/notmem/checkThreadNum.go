package notmem

import (
	"fmt"
	"slave-server/staticdata"
	"time"
)

func CheckThreadNum() int {
	for {
		time.Sleep(time.Duration(staticdata.Checktimes) * time.Second)
		fmt.Println("there are", staticdata.ThreadNum, "threads still alive")
	}
}
