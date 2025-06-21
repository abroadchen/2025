package main

import (
	"fmt"
	"os/exec"
	"time"
)

type CONN2 struct {
	servername string
	times      float64
}

func main() {
	start := time.Now()
	cmd := exec.Command("ping", "www.baidu.com")
	buf, _ := cmd.Output()
	fmt.Println(string(buf), time.Since(start))
}
