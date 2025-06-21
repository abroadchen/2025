package threadsafenetwork

import (
	"bytes"
	"encoding/binary"
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
