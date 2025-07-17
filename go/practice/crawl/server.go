/*
Package crawl

	@author: chen
	@since: 2025/7/15
	@desc:
*/
package crawl

import (
	"bufio"
	"container/list"
	"fmt"
	"net"
	"os"
	"sync"
	"time"
)

var mutex2 sync.Mutex

func main() {
	// @author By chen 2025/7/16 06:36:00
	// @Reason 写入文件
	// @Demand Version
	path := ""
	savefile, _ := os.Create(path)
	defer savefile.Close()
	save := bufio.NewWriter(savefile)

	tcpaddr1, err := net.ResolveTCPAddr("tcp4", ":8848")
	if err != nil {
		fmt.Println(err)
	}
	conn1, err := net.DialTCP("tcp", nil, tcpaddr1)
	if err != nil {
		fmt.Println(err)
	}

	go ServerMsgHandler(conn1, save)

	tcpaddr2, err := net.ResolveTCPAddr("tcp4", ":8849")
	if err != nil {
		fmt.Println(err)
	}
	conn2, err := net.DialTCP("tcp", nil, tcpaddr2)
	if err != nil {
		fmt.Println(err)
	}

	go ServerMsgHandler(conn2, save)

	conn := make([]net.Conn, 2)
	conn[0] = conn1
	conn[1] = conn2

	//for i := 0; i < 10; i++ {
	//	mystr := "xx" + strconv.Itoa(i)
	//	mystrlen := len(mystr)
	//	mybstart := IntToBytes(mystrlen)
	//	conn.Write(mybstart)
	//	conn.Write([]byte(mystr))
	//	time.Sleep(1 * time.Second)
	//}

	go func() {
		url := "https://mail.google.com/mail/"

		myqueue := list.New()
		myqueue.PushBack(url)
		level := 0
		for myqueue.Len() != 0 {
			myurl := myqueue.Front()
			fmt.Println(myurl.Value.(string))

			mystr := myurl.Value.(string)
			mystrlen := len(mystr)
			mybstart := IntToBytes(mystrlen)
			conn[level%len(conn)].Write(mybstart)
			conn[level%len(conn)].Write([]byte(mystr))

			myqueue.Remove(myurl)
			urllist := GetURL2(myurl.Value.(string))
			for _, geturl := range urllist {
				myqueue.PushBack(geturl)
			}
			level++
			if level > 3 {
				break
			}
		}
	}()

	time.Sleep(10 * time.Second)

}

func ServerMsgHandler(conn net.Conn, save *bufio.Writer) {

	//arr := []int{}
	for {
		buf1 := make([]byte, 8)
		n, err := conn.Read(buf1)
		if err != nil || n != 8 {
			fmt.Println("Server close")
			return
		}
		len1 := BytesToInt(buf1)
		buf2 := make([]byte, len1)
		n, err = conn.Read(buf2)
		if err != nil || n != len1 {
			fmt.Println("Server close")
			return
		}

		fmt.Println(string(buf2), conn.RemoteAddr())

		mutex2.Lock()
		fmt.Fprintln(save, string(buf2)+"\n")
		save.Flush()
		mutex2.Unlock()

		//if n == 16 {
		//	data1 := BytesToInt(buf[:len(buf)/2])
		//	data2 := BytesToInt(buf[len(buf)/2:])
		//	if data1 == 0 && data2 == 0 {
		//		arr = make([]int, 0)
		//	}
		//	if data1 == 1 {
		//		arr = append(arr, data2)
		//	}
		//	if data1 == 0 && data2 == 1 {
		//		fmt.Println("数组接收完成", arr)
		//		arr = make([]int, 0)
		//	}
		//}
	}
}
