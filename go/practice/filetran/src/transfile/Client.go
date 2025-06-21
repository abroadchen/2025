package main

import (
	"fmt"
	"io"
	"net"
	"os"
)

func SendFile(conn net.Conn, filePath string) {
	f, err := os.Open(filePath)
	if err != nil {
		fmt.Println("os.Open err", err)
		return
	}
	defer f.Close()

	buf := make([]byte, 4096)
	for {
		n, err := f.Read(buf)
		if err != nil {
			if err == io.EOF {
				fmt.Println("file sended")
			} else {
				fmt.Println("read file err", err)
			}
			return
		}

		_, err = conn.Write(buf[:n])
		if err != nil {
			fmt.Println("write file err", err)
			return
		}
	}
}

func main() {

	path := ""
	fileInfo, err := os.Stat(path)
	if err != nil {
		fmt.Println("os.Stat err", err)
		return
	}
	fmt.Println("filename", fileInfo.Name())
	fmt.Println("filesize", fileInfo.Size())

	conn, err := net.Dial("tcp", "127.0.0.1:9000")
	if err != nil {
		fmt.Println("net.Dial err", err)
		return
	}
	defer conn.Close()

	_, err = conn.Write([]byte(fileInfo.Name()))
	if err != nil {
		fmt.Println("conn.Write err", err)
		return
	}

	buf := make([]byte, 16)
	n, err := conn.Read(buf)
	if err != nil {
		fmt.Println("conn.Read err", err)
		return
	}
	if "ok" == string(buf[:n]) {
		SendFile(conn, path)
	}
}
