package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
	"strconv"
	"strings"
)

func handleConn(conn net.Conn) {
	defer conn.Close()
	scanner := bufio.NewScanner(conn)
	i := 0
	//for scanner.Scan() {
	//	ln := scanner.Text()
	//	fmt.Println(ln)
	//	if i == 0 {
	//		method := strings.Fields(ln)[0]
	//		fmt.Println(method)
	//	} else {
	//		if ln == "" {
	//			break
	//		}
	//	}
	//	i++
	//}

	headers := map[string]string{}
	var url, method string
	for scanner.Scan() {
		ln := scanner.Text()
		fmt.Println(ln)
		if i == 0 {
			fs := strings.Fields(ln)
			method = fs[0]
			url = fs[1]
			fmt.Println(method)
			fmt.Println(url)
		} else {
			if ln == "" {
				break
			}
			fs := strings.SplitN(ln, ": ", 2)
			headers[fs[0]] = fs[1]
		}
		i++
	}

	if method == "POST" || method == "PUT" {
		amt, _ := strconv.Atoi(headers["Content-Length"])
		buf := make([]byte, amt)
		io.ReadFull(conn, buf[:amt])
		fmt.Println("BODY:", string(buf[:amt]))
	}

	body := ""
	//io.WriteString(conn, "HTTP/1.1 200 Connection closed.\r\n")
	io.WriteString(conn, "HTTP/1.1 302 OK\r\n") //重定向
	fmt.Fprintf(conn, "Content-Length: %d\r\n", len(body))
	fmt.Fprintf(conn, "Content-Type: text/html; charset=utf-8\r\n")
	fmt.Fprintf(conn, "Location: http://www.biying.com\r\n")
	io.WriteString(conn, "\r\n")
	io.WriteString(conn, body)
}

func main() {
	server, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Fatalln(err.Error())
	}
	defer server.Close()

	for {
		conn, err := server.Accept()
		if err != nil {
			log.Fatalln(err.Error())
		}
		go handleConn(conn)
	}
}
