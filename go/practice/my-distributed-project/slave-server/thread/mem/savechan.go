package mem

import (
	"fmt"
	"slave-server/staticdata"
	"slave-server/thread/network"
)

func SaveEmailChan(r network.ReturnEmail) {
	for {
		select {
		case e, ok := <-staticdata.Emailchan:
			if ok {
				fmt.Println("received ", e)
				staticdata.Mylog.Loger.Println(e)
				r.SaveMail(e)
			}
		}
	}
}
