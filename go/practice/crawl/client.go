/*
Package crawl

	@author: chen
	@since: 2025/7/15
	@desc: 字符串网络传输
*/
package crawl

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"io"
	"log"
	"net"
	"net/http"
	"regexp"
	"sync"
)

var mutex sync.Mutex

func main() {
	server_listener, err := net.Listen("tcp", ":8848")
	if err != nil {
		log.Fatal(err)
	}
	defer server_listener.Close()
	for {
		new_conn, err := server_listener.Accept()
		if err != nil {
			log.Fatal(err)
		}
		go MsgHandle(new_conn)
	}
}

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

func MsgHandle(conn net.Conn) {

	defer conn.Close()
	//arr := []int{}
	for {
		buf1 := make([]byte, 8)
		n, err := conn.Read(buf1)
		if err != nil || n != 8 {
			fmt.Println("client close")
			return
		}
		len1 := BytesToInt(buf1)
		buf2 := make([]byte, len1)
		n, err = conn.Read(buf2)
		if err != nil || n != len1 {
			fmt.Println("client close")
			return
		}

		url := string(buf2)
		go func() {
			getMail2(url, conn)
		}()
		//fmt.Println(string(buf2))
		//mystr := "收到" + string(buf2)
		//mystrlen := len(mystr)
		//mybstart := IntToBytes(mystrlen)
		//conn.Write(mybstart)
		//conn.Write([]byte(mystr))

		//conn.Write(buf)
		//if n == 16 {
		//	data1 := BytesToInt(buf[:len(buf)/2])
		//	data2 := BytesToInt(buf[len(buf)/2:])
		//	if data1 == 0 && data2 == 0 {
		//		arr = make([]int, 0, 0)
		//	}
		//	if data1 == 1 {
		//		arr = append(arr, data2)
		//	}
		//	if data1 == 0 && data2 == 1 {
		//		fmt.Println("数组接收完成", arr)
		//		sort.Ints(arr)
		//		fmt.Println("数组排序完成", arr)
		//		mybstart := IntToBytes(0)
		//		mybstart = append(mybstart, IntToBytes(0)...)
		//		conn.Write(mybstart)
		//
		//		for i := 0; i < len(arr); i++ {
		//			mybdata := IntToBytes(1)
		//			mybdata = append(mybdata, IntToBytes(1)...)
		//			conn.Write(mybdata)
		//		}
		//
		//		mybend := IntToBytes(0)
		//		mybend = append(mybend, IntToBytes(0)...)
		//		conn.Write(mybend)
		//
		//		arr = make([]int, 0, 0)
		//	}
		//}
	}
}

func getMail2(url string, conn net.Conn) []string {
	resp, err := http.Get(url)
	if err != nil {
		return []string{}
	}
	b, err := io.ReadAll(resp.Body)
	if err != nil {
		return []string{}
	} //qq ^[1-9]\\d{4,10}$
	reg := `^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(.[a-zA-Z0-9_-]+)+$`
	rgx := regexp.MustCompile(reg)
	tmplist := rgx.FindAllString(string(b), -1)

	mutex.Lock()
	for _, email := range tmplist {
		if len(email) != 0 {
			mystr := email
			mystrlen := len(mystr)
			mybstart := IntToBytes(mystrlen)
			conn.Write(mybstart)
			conn.Write([]byte(mystr))
		}
	}
	mutex.Unlock()
	return tmplist
}
