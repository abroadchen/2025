package mem

import (
	"fmt"
	"master-server/data-server/store/savetxt"
	"slave-server/staticdata"
)

func SaveEmailChan(path string) {
	var sf store.SaveData
	sf = savetxt.NewSafeFile(path)
	i := 0
	maillist := []string{}
	for {
		select {
		case e, ok := <-staticdata.Emailchan:
			if ok {
				fmt.Println("received ", e)
				staticdata.Mylog.Loger.Println(e)
				maillist = append(maillist, e)
				i++
				if i%10 == 0 {
					sf.WriteLines(maillist)
					maillist = []string{}
				}
			}
		}
	}
}
