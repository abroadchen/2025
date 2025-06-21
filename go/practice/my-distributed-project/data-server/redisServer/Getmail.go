package redisServer

import (
	"data-server/mongoserver"
	"data-server/staticdata"
	"fmt"
	"github.com/garyburd/redigo/redis"
	"strconv"
	"time"
)

func GetMailRedisMultiThread() {
	var database_redis_queue = &ThreadQueue.Connect_args{
		Queue_name: "databasemail",
		Network:    "tcp",
		Address:    "localhost:6379",
		Password:   "",
		Client:     nil,
	}
	database_redis_queue.Create_queue()
	mygo := mongoserver.NewMongoDB("mongodb://127.0.0.1:27017", "test", "mail")
	for {
		value, _ := database_redis_queue.Get()
		if len(value) == 0 {
			time.Sleep(1 * time.Second)
		} else {
			emailstr := value
			isok := staticdata.Mailmap.Isin(emailstr)
			if isok {
				num := staticdata.Mailmap.Get(emailstr)
				numint, _ := strconv.Atoi(num)
				staticdata.Mailmap.Set(emailstr, strconv.Itoa(1+numint))
			} else {
				staticdata.Mailmap.Set(emailstr, strconv.Itoa(1))
				fmt.Println("take", emailstr)
				if staticdata.IsMongo {
					mygo.InsertData(emailstr)
				}
				go func(email string) {
					c, err := redis.Dial("tcp", "localhost:6379")
					if err != nil {
						fmt.Println(err)
						return
					}
					defer c.Close()
					c.Send("SET", emailstr, "1")
					c.Send("GET", emailstr)
					c.Flush()
					c.Receive()
					v, err := c.Receive()
					if err != nil {
						fmt.Println(err)
						return
					}
					if string(v.([]byte)) == "1" {
						fmt.Println("save success")
					} else {
						fmt.Println("save fail")
					}
				}(emailstr)
			}
		}
	}
	database_redis_queue.Close()
}
