package main

import (
	"fmt"
	"io"
	"net/http"
	"net/http/httptrace"
	"os"
)

func main() {
	URL := ""
	client := http.Client{}
	req, _ := http.NewRequest("GET", URL, nil)
	trace := &httptrace.ClientTrace{
		GotFirstResponseByte: func() {
			fmt.Println("First response byte")
		},
		GotConn: func(connInfo httptrace.GotConnInfo) {
			fmt.Println("Got Conn: %+v\n", connInfo)
		},
		DNSDone: func(dnsinfo httptrace.DNSDoneInfo) {
			fmt.Println("DNS Done: %+v\n", dnsinfo)
		},
		ConnectStart: func(network, addr string) {
			fmt.Println("Connect Start")
		},
		ConnectDone: func(network, addr string, err error) {
			fmt.Println("Connect Done")
		},
		WroteHeaders: func() {
			fmt.Println("Wrote Headers")
		},
	}
	req = req.WithContext(httptrace.WithClientTrace(req.Context(), trace))
	fmt.Println("requesting data from server")
	_, err := http.DefaultTransport.RoundTrip(req)
	if err != nil {
		fmt.Println(err)
		return
	}
	respons, err := client.Do(req)
	if err != nil {
		fmt.Println(err)
		return
	}
	io.Copy(os.Stdout, respons.Body)
}
