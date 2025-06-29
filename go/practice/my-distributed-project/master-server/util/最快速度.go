package util

import (
	"fmt"
	"os/exec"
	"time"
)

type CONN struct {
	servername string
	times      float64
}

func main() {
	starttime := time.Now()
	cmd := exec.Command("ping", "www.baidu.com")
	buf, _ := cmd.Output()
	fmt.Println(string(buf))
	fmt.Println(time.Since(starttime))
}
