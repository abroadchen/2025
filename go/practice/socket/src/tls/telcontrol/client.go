package main

import (
	"crypto/tls"
	"fmt"
	"log"
)

func main() {
	log.SetFlags(log.Lshortfile)
	conf := &tls.Config{
		InsecureSkipVerify: true,
	}
	conn, err := tls.Dial("tcp", "127.0.0.1:8000", conf)
	if err != nil {
		log.Println(err)
		return
	}
	defer conn.Close()

	for {
		var input string
		fmt.Scanf("%s\n", &input)
		n, err := conn.Write([]byte(input + "\n"))
		if err != nil {
			log.Println(n, err)
			return
		}
		buf := make([]byte, 100)
		n, err = conn.Read(buf)
		if err != nil {
			log.Println(n, err)
			return
		}
		println(string(buf[:n]))
	}

}
