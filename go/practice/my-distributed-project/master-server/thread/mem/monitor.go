package mem

import (
	"slave-server/staticdata"
	"time"
)

func Monitor() {
	for {
		list1, _ := staticdata.Mailmap.Getall()
		if len(list1) > 100000 {

		}
		list2, _ := staticdata.Urlmap.Getall()
		if len(list2) > 100000 {

		}
		time.Sleep(time.Second * 60 * 10)
	}
}
