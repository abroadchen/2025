package mem

import (
	"fmt"
	"slave-server/myerror"
	"slave-server/staticdata"
	"slave-server/webPageGet"
	"slave-server/webPageGet/GetMail"
)

func EmailDeduplication(url string) []string {
	myu := webPageGet.WebGet{url, []func(string2 string) []string{GetMail.GetMail}}
	maillist := myu.Getfunc[0](myu.Url)
	return maillist
}

func EmailChanThread() error {
	for {
		if elem, ok := <-staticdata.Urlchan; ok {
			emaillist := EmailDeduplication(elem)
			for _, email := range emaillist {
				staticdata.Emailchan <- email
			}
		} else {
			fmt.Println("Email channel closed")
			staticdata.Mylog.Loger.Println("fainal err, channel has closed")
			mychanerr := new(myerror.Chanerr)
			return mychanerr
		}
	}
	return nil
}
