package staticdata

import (
	"master-server/datastruct/myMap"
	"master-server/etcd"
	"master-server/log"
)

var DataETCDServer *etcd.ETCDKV = etcd.NewETCDKV()
var Mylog *log.Logfile = nil
var Checktimes = 3
var ThreadNum int64 = 1000
var Urlmap = myMap.NewMyMap()
var Mailmap = myMap.NewMyMap()
var Cache = 3000
var MAXTHREADNUM int64 = 100000
var LoadBalance = 0
var Urlchan = make(chan string, 1000)
var IsMongo = true
