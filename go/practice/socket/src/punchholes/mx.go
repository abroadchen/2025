package main

import (
	"fmt"
	"net"
)

func main() {
	domain := "qq.com"
	mxs, err := net.LookupMX(domain)
	if err != nil {
		fmt.Println(err)
		return
	}
	for _, mx := range mxs {
		fmt.Println(mx.Host)
	}
}
