package main

import (
	"data-server/database"
	"data-server/nsqserver"
	"data-server/redisServer"
	"data-server/staticdata"
	"fmt"
	"time"
)

func init() {
	staticdata.DataETCDServer.Set("IsNSQ", "true")
	staticdata.DataETCDServer.Set("mongoDBpath", "mongodb://127.0.0.1:27017")
}

func main() {
	res := staticdata.DataETCDServer.Get("IsNSQ")
	if res == "true" {

		var savetxt database.SaveData = database.NewSafeFile("mail.txt")
		var savemongo database.SaveData = database.NewMongoDB("mongodb://127.0.0.1:27017", "test", "mail")
		var savemysql *database.MySQLclient = database.NewMySQLclient("127.0.0.1", "root", "111111", "")
		myConsumer := nsqserver.NewMyConsumer("save_email", "chanel", []database.SaveData{savetxt, savemongo, savemysql})
		fmt.Println(myConsumer)
	} else {
		redisServer.GetMailRedisMultiThread()
	}

	for {
		time.Sleep(1 * time.Second)
		fmt.Println(time.Now())
	}
}
