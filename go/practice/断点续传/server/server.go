package server

import (
	"fmt"
	"io"
	"net"
	"os"
	"strconv"
)

// WriteFile
//
//	@Description: 追加
//	@param content
func WriteFile(content []byte) {
	if len(content) > 0 {
		fp, err := os.OpenFile("sr_1.txt", os.O_WRONLY|os.O_CREATE|os.O_APPEND, 0777)
		if err != nil {
			fmt.Println("open file err", err)
		}
		defer fp.Close()
		_, err = fp.Write(content)
		if err != nil {
			fmt.Println("write file err", err)
		}
		fmt.Println("写入成功")
	}
}

// getfilestat
//
//	@Description: 判断文件是否存在 提取大小
//	@return int64
func getfilestat() int64 {
	fileinfo, err := os.Stat("sr_1.txt")
	if err != nil {
		if os.IsNotExist(err) {
			return 0
		}
	}
	return fileinfo.Size()
}

// ServerConn
//
//	@Description:
//	@param conn
func ServerConn(conn net.Conn) {
	defer conn.Close()
	for {
		var buf = make([]byte, 10)
		n, err := conn.Read(buf)
		if err != nil {
			if err == io.EOF {
				fmt.Println("server is EOF", err)
				return
			}
			fmt.Println("server read err", err)
			return
		}
		fmt.Println("收到", string(buf[:n]))
		switch string(buf[:n]) {
		case "start->":
			off := getfilestat()
			stringoff := strconv.FormatInt(off, 10)
			_, err := conn.Write([]byte(stringoff))
			if err != nil {
				fmt.Println("server Write err", err)
			}
			continue
		case "<-end":
			fmt.Println("文件写入成功")
			return
		}
		WriteFile(buf[:n])
	}
}

// main
//
//	@Description:
func main() {
	sr, err := net.Listen("tcp", ":8848")
	if err != nil {
		fmt.Println("listen err", err)
	}
	defer sr.Close()

	for {
		conn, err := sr.Accept()
		if err != nil {
			fmt.Println("accept err", err)
		}

		ServerConn(conn)
	}
}
