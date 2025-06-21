package staticdata

import (
	"slave-server/etcd"
	"slave-server/log"
)

var DataETCDServer *etcd.ETCDKV = etcd.NewETCDKV()
var Mylog *log.Logfile = nil
var Checktimes = 3
var ThreadNum int64 = 1000
var IsMEM bool = true
var Urlchan = make(chan string, Cache)
var Emailchan = make(chan string, Cache)
var Cache = 3000
var MAXTHREADNUM int64 = 100000
var IsNSQ = true
