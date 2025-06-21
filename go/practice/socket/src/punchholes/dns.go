package main

import (
	"context"
	"flag"
	"fmt"
	"net"
)

func main1() {
	domain := "baidu.com"
	ns, err := net.LookupNS(domain)
	if err != nil {
		fmt.Println(err)
		return
	}
	for _, n := range ns {
		fmt.Println(n.Host)
	}
}

var hostFlag = flag.String("host", "8.8.8.8:53", "host DNS server")

func main() {
	flag.Parse()
	host := *hostFlag
	var r net.Resolver
	r.Dial = func(ctx context.Context, network, addr string) (net.Conn, error) {
		fmt.Println("was going to use DNS server at", addr)
		return net.Dial(network, "208.67.222.123:53")
	}
	r.PreferGo = true
	res, err := r.LookupHost(context.Background(), host)
	fmt.Println(res, err)
}
