package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"net/http"
	"strings"
)

type HTTPProxy struct {
	Addr string
	Port string
}

func StartHTTPProxy(addr, port string) {
	proxy := &HTTPProxy{
		Addr: addr,
		Port: port,
	}
	log.Printf("HTTPProxy is running on #{proxy.Addr}:#{proxy.Port}\n")
	log.Fatalln(http.ListenAndServe(proxy.Addr+":"+proxy.Port, proxy))
}

func (p *HTTPProxy) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Received request: #{r.Method} #{r.Host} #{r.RemoteAddr}\n")
	tranport := http.DefaultTransport
	outReq := new(http.Request)
	*outReq = *r
	if clientIP, _, err := net.SplitHostPort(outReq.RemoteAddr); err == nil {
		if prior, ok := outReq.Header["X-Forwarded-For"]; ok {
			clientIP = strings.Join(prior, ", ") + ", " + clientIP
		}
		outReq.Header.Set("X-Forwarded-For", clientIP)
	}
	resp, err := tranport.RoundTrip(outReq)
	if err != nil {
		w.WriteHeader(http.StatusBadGateway)
		return
	}
	defer resp.Body.Close()

	for key, value := range resp.Header {
		for _, v := range value {
			w.Header().Add(key, v)
		}
	}
	w.WriteHeader(resp.StatusCode)
	_, _ = io.Copy(w, resp.Body)
}
