package threadrun

import (
	"fmt"
	"net"
	"slave-server/staticdata"
	"slave-server/thread/notmem"
)

func MsgHandle(conn net.Conn) {
	defer conn.Close()
	for {
		buf := make([]byte, 8)
		n, err := conn.Read(buf)
		if err != nil || n != 8 {
			fmt.Println("read err: ", conn)
			return
		}
		length := BytesToInt(buf)
		buf2 := make([]byte, length)
		n, err = conn.Read(buf2)
		if err != nil || n != length {
			fmt.Println("read err: ", conn)
			return
		}
		fmt.Println("receive: ", string(buf2))
		myr := NewReturnEmail(conn)
		if staticdata.IsMEM {
			staticdata.Urlchan <- string(buf2)
		} else {
			go notmem.GetMailThread(*myr, string(buf2))
		}
	}
}
