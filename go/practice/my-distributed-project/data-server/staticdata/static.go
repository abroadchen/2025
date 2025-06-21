package staticdata

import (
	"data-server/database"
	"data-server/datastruct/MyRedisMap"
	"data-server/etcd"
)

var Checktimes = 3
var ThreadNum int64 = 1000
var Urlmap = MyRedisMap.NewMyRedisMap(7, "", "localhost:6379")
var Mailmap = MyRedisMap.NewMyRedisMap(8, "", "localhost:6379")
var Cache = 3000
var MAXTHREADNUM int64 = 100000
var LoadBalance = 0
var Urlchan = make(chan string, 1000)
var IsMongo = true
var IsNSQ = true
var SaveDatafuncs []database.SaveData = []database.SaveData{}
var DataETCDServer *etcd.ETCDKV = etcd.NewETCDKV()
