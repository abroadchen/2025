package single

import "os"

var Cachepath = ""
var Qqpath = ""
var QqIndexPath = ""
var QqNamePath = ""

var Qfindex, _ = os.Open(QqIndexPath)
var Qfi, _ = os.Open(QqNamePath)
