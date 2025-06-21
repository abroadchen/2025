package controlsendemail

import (
	"controlsendemail/nsq"
)

func main() {
	nsq.NSQThread()
	//mydb := db.NewMySQLclient("")
	//mydb.UpdateSendEmailStat("", 1)
}
