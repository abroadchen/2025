package main

import (
	"fmt"
	"github.com/garyburd/redigo/redis"
	"time"
)

func Push(message string) {
	c, _ := redis.Dial("tcp", "localhost:6379")
	_, err := c.Do("PUBLISH", "dataservercmd", message)
	if err != nil {
		fmt.Println(err)
		return
	}
}

func subs() {
	c, err := redis.Dial("tcp", "localhost:6379")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer c.Close()
	psc := redis.PubSubConn{c}
	psc.Subscribe("dataservercmdresult")
	for {
		switch v := psc.Receive().(type) {
		case redis.Message:
			fmt.Println(v.Channel, string(v.Data), "message")
			fmt.Println("收到结果")
		case redis.Subscription:
			fmt.Println(v.Channel, v.Count, v.Kind, "")
		case error:
			fmt.Println(v)
			return
		}
	}
}

func main() {
	go subs()
	for {
		var input string
		fmt.Scanln(&input)
	}
}
