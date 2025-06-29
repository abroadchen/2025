package single

import (
	"os"
	"sync"
)

var Cachepath = ""
var Qqpath = ""
var QqIndexPath = ""
var QqNamePath = ""

var Qfindex, _ = os.Open(QqIndexPath)
var Qfi, _ = os.Open(QqNamePath)
var mutex = new(sync.Mutex)
