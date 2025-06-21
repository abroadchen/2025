package thread

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"master-server/data-server/store/savetxt"
	"net"
)

func IntToBytes(n int) []byte {
	data := int64(n)
	bytebuf := bytes.NewBuffer([]byte{})
	binary.Write(bytebuf, binary.BigEndian, data)
	return bytebuf.Bytes()
}

func BytesToInt(b []byte) int {
	bytebuf := bytes.NewBuffer(b)
	var data int64
	binary.Read(bytebuf, binary.BigEndian, &data)
	return int(data)
}

func ServerMsgHandler(conn net.Conn, file *savetxt.SafeFile) {
	defer conn.Close()
	for {
		buf := make([]byte, 8)
		n, err := conn.Read(buf)
		if err != nil || n != 8 {
			fmt.Println("read err: ", conn)
			return
		}
		length := BytesToInt(buf)
		if length > 1 && length < 10000 {
			buf2 := make([]byte, length)
			n, err = conn.Read(buf2)
			if err != nil || n != length {
				fmt.Println("read err: ", conn)
				return
			}
			fmt.Println("receive: ", string(buf2))
			file.WriteLine(string(buf2))
		}
	}
}
