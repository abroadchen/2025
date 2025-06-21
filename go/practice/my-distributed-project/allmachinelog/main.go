package allmachinelog

import (
	"allmachinelog/nsq"
	"fmt"
)

func main() {
	nsq.NSQThread()

	myProduct := nsq.NewMyProduct()
	for i := 0; i < 100; i++ {
		myProduct.Pub("Log", fmt.Sprintf("%s %s %s %d", "127.0.0.1", "2222222", "server ok", 1))
	}
}

//func main1() {
//	mydb := mysql.NewMySQLclient("127.0.0.1", "root", "111111", "")
//	mydb.Add(log.NewLogInfo(1, "12.12.12.11", ""))
//}
