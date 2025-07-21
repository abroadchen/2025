package client

import (
	"fmt"
	"io"
	"net"
	"os"
	"strconv"
	"time"
)

func clientRead(conn net.Conn) int {
	buf := make([]byte, 5)
	n, err := conn.Read(buf)
	if err != nil {
		fmt.Println("clientRead err", err)
	}
	off, err := strconv.Atoi(string(buf[:n]))
	if err != nil {
		fmt.Println("a2i err", err)
	}
	return off
}

func clientWrite(conn net.Conn, data []byte) {
	_, err := conn.Write(data)
	if err != nil {
		fmt.Println("clientWrite err", err)
	}
	fmt.Println("clientWrite ok", string(data))
}

func clientConn(conn net.Conn) {
	defer conn.Close()
	clientWrite(conn, []byte("start->"))
	off := clientRead(conn)

	fp, err := os.OpenFile("1.txt", os.O_RDONLY, 0777)
	if err != nil {
		fmt.Println("open file err", err)
	}
	defer fp.Close()

	_, err = fp.Seek(int64(off), 0)
	if err != nil {
		fmt.Println("seek file err", err)
	}

	for {
		data := make([]byte, 10)
		n, err := fp.Read(data)
		if err != nil {
			if err == io.EOF {
				time.Sleep(time.Millisecond * 100)
				clientWrite(conn, []byte("<-end"))
				fmt.Println("send all ok")
				break
			}
		}
		time.Sleep(time.Millisecond * 100)
		clientWrite(conn, data[:n])
	}

}

func main() {
	conn, err := net.DialTimeout("tcp", "127.0.0.1:8848", time.Second)
	if err != nil {
		fmt.Println("main err", err)
	}
	clientConn(conn)
}
