package main

import (
	"io"
	"log"
	"net"
	"net/http"
	"strings"
)

type Proxy struct {
	Addr        string
	Port        string
	IsAnonymous bool
	Debug       bool
}

func NewProxy(addr, port string, anony, debug bool) *Proxy {
	return &Proxy{
		Addr:        addr,
		Port:        port,
		IsAnonymous: anony,
		Debug:       debug,
	}
}

func (p *Proxy) ServeHTTP(rw http.ResponseWriter, r *http.Request) {
	if p.Debug {
		log.Printf("received request #{r.Method} #{r.Host} #{r.RemoteAddr}\n")
	}
	if r.Method != http.MethodConnect {
		p.HTTP(rw, r)
	} else {
		p.HTTPS(rw, r)
	}
}

func (p *Proxy) HTTP(rw http.ResponseWriter, req *http.Request) {
	transport := http.DefaultTransport
	outReq := new(http.Request)
	*outReq = *req
	if !p.IsAnonymous {
		if clientIP, _, err := net.SplitHostPort(req.RemoteAddr); err == nil {
			if prior, ok := outReq.Header["X-Forwarded-For"]; ok {
				clientIP = strings.Join(prior, ", ") + ", " + clientIP
			}
			outReq.Header.Set("X-Forwarded-For", clientIP)
		}
	}
	resp, err := transport.RoundTrip(outReq)
	if err != nil {
		rw.WriteHeader(http.StatusBadGateway)
		rw.Write([]byte(err.Error()))
		return
	}
	defer resp.Body.Close()
	for key, value := range resp.Header {
		for _, v := range value {
			rw.Header().Add(key, v)
		}
	}
	rw.WriteHeader(resp.StatusCode)
	_, _ = io.Copy(rw, resp.Body)
}

func (p *Proxy) HTTPS(rw http.ResponseWriter, r *http.Request) {
	host := r.URL.Host
	hij, ok := rw.(http.Hijacker)
	if !ok {
		log.Printf("HTTP Server does not support hijacking\n")
	}
	client, _, err := hij.Hijack()
	if err != nil {
		log.Fatalln("hijack", err)
	}
	server, err := net.Dial("tcp", host)
	if err != nil {
		log.Fatalln("Dial host:", err)
	}
	client.Write([]byte("HTTP/1.1 200 Connection established\r\n\r\n"))
	go io.Copy(server, r.Body)
	go io.Copy(client, r.Body)
}
