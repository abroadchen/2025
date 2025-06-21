package nsq

import "controlsendemail/db"

func NSQThread() {
	mydb := db.NewMySQLclient("URL", "")
	mymaillist := mydb.GetallEmail()
	myp := NewMyProduct()
	for _, email := range mymaillist {
		myp.Pub("ToSend", email)
	}
	mychan := make(chan int)
	<-mychan
}
