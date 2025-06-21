package main

import (
	"bufio"
	"bytes"
	"errors"
	"fmt"
	"log"
	"net"
	"net/http"
	"os"
	"path/filepath"
	"strconv"
)

const (
	NETWORK     = "tcp"
	SERVER_IP   = "127.0.0.1"
	SERVER_PORT = 8000
	BUFF_SIZE   = 8
	REQ_FILE    = ""
)

func main() {
	log.Println("client start")
	serverAddr := SERVER_IP + ":" + strconv.Itoa(SERVER_PORT)
	conn, err := dialServer(serverAddr)
	if err != nil {
		log.Fatalf("connect server #{serverAddr} failed, #{err} quit\n")
	}
	defer conn.Close()
	log.Println("connect server #{serverAddr} success\n")

	var file *os.File
	file, err = requestFile(conn, REQ_FILE)
	if err != nil {
		log.Fatalf("to server #{serverAddr} request file #{REQ_FILE} failed, #{err}\n")
	}
	defer file.Close()
}

func dialServer(serverAddr string) (net.Conn, error) {
	conn, err := net.Dial(NETWORK, serverAddr)
	if err != nil {
		log.Printf("connect server #{serverAddr} failed, retry\n")
		conn, err := net.Dial(NETWORK, serverAddr)
		if err != nil {
			log.Fatalf("second #{serverAddr} failed, quit\n")
			return nil, err
		}
		return conn, nil
	}
	return conn, nil
}

func requestFile(conn net.Conn, filePath string) (*os.File, error) {
	method := http.MethodGet
	url := filePath
	version := "HTTP/1.1"
	header := method + " " + url + " " + version + "\n\n"
	_, err := conn.Write([]byte(header))
	if err != nil {
		log.Println("send header failed", header)
		return nil, err
	}
	curPath, err := filePath.Abs(os.Args[0])
	if err != nil {
		return nil, err
	}
	curDir := filepath.Dir(curPath)
	filename := curDir + filePath
	fmt.Println(filename)
	file, err := os.Create(filename)
	if err != nil {
		return nil, err
	}
	r := bufio.NewReader(conn)
	respHeader, _, err := r.ReadLine()
	if err != nil {
		return nil, err
	}
	respH := bytes.Split(respHeader, []byte(" "))
	fmt.Println(string(respHeader))
	if string(respH[2]) != http.StatusText(http.StatusOK) {
		return nil, errors.New("404")
	}

	buf := make([]byte, BUFF_SIZE)
	r.ReadLine()
	for {
		n, err := r.Read(buf)
		if n < BUFF_SIZE {
			_, err = file.Write(buf[:n])
			if err != nil {
				return nil, err
			}
			log.Println("finished")
			return file, nil
		}
		if err != nil {
			return nil, err
		}
		_, err = file.Write(buf[:n])
		if err != nil {
			return nil, err
		}
	}
}
