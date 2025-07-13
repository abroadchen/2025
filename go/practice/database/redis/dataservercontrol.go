package main

import (
	"bytes"
	"fmt"
	"github.com/garyburd/redigo/redis"
	//"github.com/go-redis/redis/v8"
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
	c, err := redis.Dial("tcp", "localhost:6379")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer c.Close()
	psc := redis.PubSubConn{c}
	psc.Subscribe("dataservercmd")
	for {
		switch v := psc.Receive().(type) {
		case redis.Message:
			fmt.Println(v.Channel, string(v.Data), "message")
			returnstr := runcmd(string(v.Data))
			func() {
				c, _ := redis.Dial("tcp", "localhost:6379")
				_, err := c.Do("PUBLISH", "dataservercmdresult", returnstr)
				if err != nil {
					fmt.Println(err)
					return
				}
			}()
			time.Sleep(time.Second)
		case redis.Subscription:
			fmt.Println(v.Channel, v.Count, v.Kind, "")
		case error:
			fmt.Println(v)
			return
		}
	}
}

func QQislive() {
	for {
		time.Sleep(time.Second * 10)
		laststr := runcmd("tasklist")
		if strings.Contains(laststr, "QQ.exe") {
			func() {
				c, _ := redis.Dial("tcp", "localhost:6379")
				_, err := c.Do("PUBLISH", "QQresult", "QQlive")
				if err != nil {
					fmt.Println(err)
					return
				}
			}()
			time.Sleep(time.Second)
		} else {
			func() {
				c, _ := redis.Dial("tcp", "localhost:6379")
				_, err := c.Do("PUBLISH", "QQresult", "QQdie")
				if err != nil {
					fmt.Println(err)
					return
				}
			}()
		}
	}
}

func main() {
	go QQislive()
	subs()
}
