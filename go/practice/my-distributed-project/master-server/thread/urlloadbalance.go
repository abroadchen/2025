package thread

import (
	"fmt"
	"master-server/staticdata"
	"math/rand"
	"net"
)

func LoadBalanceURLChan(conns []net.Conn) {
	var i = 0
	for {
		select {
		case e, ok := <-staticdata.Urlchan:
			if ok {
				fmt.Println("received ", e)
				staticdata.Mylog.Loger.Println(e)
				i++
				if staticdata.LoadBalance == 0 {
					mystrlen := len(e)
					mybytes := IntToBytes(mystrlen)
					conns[i%len(conns)].Write(mybytes)
					conns[i%len(conns)].Write([]byte(e))
				} else if staticdata.LoadBalance == 1 {
					mystrlen := len(e)
					mybytes := IntToBytes(mystrlen)
					randnum := rand.Int()
					conns[randnum%len(conns)].Write(mybytes)
					conns[randnum%len(conns)].Write([]byte(e))
				}
			}
		}
	}
}
