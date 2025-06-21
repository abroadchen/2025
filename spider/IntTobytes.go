package spider

import (
	"bytes"
	"encoding/binary"
)

func IntTobytes(n int) []byte {
	data := int64(n)
	bytebuff := bytes.NewBuffer([]byte{})
	binary.Write(bytebuff, binary.BigEndian, data)
	return bytebuff.Bytes()
}

func BytesToInt(bts []byte) int {
	bytebuff := bytes.NewBuffer(bts)
	var data int64
	binary.Read(bytebuff, binary.BigEndian, &data)
	return int(data)
}
