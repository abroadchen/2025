package util

import (
	"crypto/md5"
	"fmt"
)

func main() {
	h := md5.New()
	h.Write([]byte("http://www.baidu.com"))
	myb := h.Sum(nil)
	data1 := BytesToInt(myb[:8])
	data2 := BytesToInt(myb[8:])
	fmt.Println(data1, data2, data1*data2)
	num := data1 * data2
	if num < 0 {
		num = -num
	}
	fmt.Println(num % 6)
}
