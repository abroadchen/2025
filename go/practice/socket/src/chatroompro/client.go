package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"time"
)

func main() {
	//conn, err := net.Dial("tcp", "127.0.0.1:8848")
	conn, err := net.DialTimeout("tcp", "", 3*time.Second)
	if err != nil {
		fmt.Println(err)
		return
	}

	done := make(chan struct{})

	go func() {
		io.Copy(os.Stdout, conn)
		log.Println("done")
		done <- struct{}{}
	}()
	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done
}

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}
