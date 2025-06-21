package main

import (
	"fmt"
	"io"
	"net"
	"net/http"
)

type handle struct {
}

func (h *handle) ServeHTTP(res http.ResponseWriter, req *http.Request) {
	//path := ""
	//bs, err := ioutil.ReadFile(path)
	//if err != nil {
	//	return
	//}
	//w.Write(bs)
	res.Header().Set("Content-Type", "text/html; charset=utf-8")
	switch req.URL.Path {
	case "/":
		io.WriteString(res, "hello world")
	case "":
		io.WriteString(res, "hello world")
	default:
		io.WriteString(res, "404")
	}

}

func main() {

	//http.Handle("", new(handle))
	//http.ListenAndServe(":8080", nil)

	conn, err := net.Dial("tcp", "127.0.0.1:8080")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer conn.Close()
	httpRequest := "Get "
	conn.Write([]byte(httpRequest))

	buf := make([]byte, 4096)
	n, _ := conn.Read(buf)
	if n == 0 {
		return
	}
	fmt.Println(string(buf[:n]))
}
