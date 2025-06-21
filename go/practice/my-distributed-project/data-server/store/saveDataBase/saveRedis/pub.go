package main

import (
	"bytes"
	"fmt"
	"github.com/garyburd/redigo/redis"
	"os/exec"
	"strings"
	"time"
)

func runcmd(cmdstr string) string {
	cmd := exec.Command(cmdstr)
	cmd.Stdin = strings.NewReader("input")
	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}

func subs() {
	c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("connect redis failed, err:", err)
		return
	}
	defer c.Close()
	psc := redis.PubSubConn{c}
	psc.Subscribe("dataservercmd")
	for {
		switch v := psc.Receive().(type) {
		case redis.Message:
			fmt.Println(v.Channel, string(v.Data), "message")
			runcmd(string(v.Data))
		case redis.Subscription:
			fmt.Printf("%s: %s %d\n", v.Channel, v.Kind, v.Count)
		case error:
			fmt.Println("error:", v)
			return
		}
	}
}

func Push(message string) {
	c, _ := redis.Dial("tcp", "127.0.0.1:6379")
	_, err1 := c.Do("PUBLISH", "my_channel", message)
	if err1 != nil {
		fmt.Println("err1:", err1)
		return
	}
}

func main() {
	go subs()
	go Push("")
	time.Sleep(5 * time.Second)
}
