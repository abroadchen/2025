package main

import (
	"context"
	"flag"
	"fmt"
	"net"
	"os"
)

func main2() {
	var (
		addr string
	)

	flag.StringVar(&addr, "addr", "127.0.0.1:8080", "address to listen on")
	flag.Parse()
	names, err := net.LookupAddr(addr)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(names)
}

func main3() {
	var (
		host string
	)
	flag.StringVar(&host, "host", "local host", "host to listen on")
	flag.Parse()
	addrs, err := net.LookupHost(host)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(addrs)
}

func main() {
	var (
		host string
	)
	flag.StringVar(&host, "host", "local host", "host to listen on")
	flag.Parse()
	res := net.Resolver{PreferGo: true}
	//addrs, err := res.LookupHost(context.Background(), host)
	addrs, err := res.LookupIPAddr(context.Background(), host)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(addrs)
}
