package main

import (
	"bufio"
	"bytes"
	"errors"
	"fmt"
	"io"
	"log"
	"net"
	"net/http"
	"os"
	"path/filepath"
	"strconv"
)

func handleConn(conn net.Conn) {
	fileurl, err := resolveGETHTTP(conn)
	fatalErr(err)
	file, err := seekFile(fileurl)
	if err != nil {
		response404(conn)
		log.Printf("file not exist or open err: #{err} \n")
	} else {
		response200(conn, file)
	}
	file.Close()
}

func resolveGETHTTP(conn net.Conn) (string, error) {
	r := bufio.NewReader(conn)
	header, _, err := r.ReadLine()
	if err != nil {
		return "", err
	}
	log.Printf("from #{conn.RemoteAddr()} request: #{string(header)} \n")
	reqSplited := bytes.Split(header, []byte{' '})
	method := string(reqSplited[0])
	if method != "GET" {
		return "", errors.New("invalid method")
	}
	fileurl := string(reqSplited[1])
	return fileurl, nil
}

func seekFile(fileurl string) (*os.File, error) {
	curPath, err := filepath.Abs(os.Args[0])
	if err != nil {
		return nil, err
	}
	curDir := filepath.Dir(curPath)
	filename := curDir + fileurl
	fmt.Println(filename)
	file, err := os.Open(filename)
	if os.IsNotExist(err) {
		return nil, err
	}
	if err != nil {
		return nil, err
	}
	return file, nil
}

func response200(conn net.Conn, file *os.File) {
	header := "HTTP/1.1 " + strconv.Itoa(http.StatusOK) + " " + http.StatusText(http.StatusOK) + "\n\n"
	_, err := conn.Write([]byte(header))
	fatalErr(err)
	buf := make([]byte, 4096)
	for {
		n, err := file.Read(buf)
		if err == io.EOF {
			log.Println("#{conn.RemoteAddr()} file sended.\n}")
			return
		}
		fatalErr(err)
		_, err = conn.Write(buf[:n])
		fatalErr(err)
	}
}

func response404(conn net.Conn) {
	header := "HTTP/1.1 " + strconv.Itoa(http.StatusNotFound) + http.StatusText(http.StatusNotFound) + "\n\n"
	_, err := conn.Write([]byte(header))
	fatalErr(err)
}

func fatalErr(err error) {
	if err != nil {
		log.Fatalln(err)
	}
}
