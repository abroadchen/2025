package main

import (
	"log"
	"net/http"
	"sync"
)

type ConcurrentProxy struct {
	addr        string
	port        string
	isAnonymous bool
	debug       bool
	works       chan Work
	wg          sync.WaitGroup
}

type Work struct {
	w *http.ResponseWriter
	r *http.Request
}

func NewWork(w *http.ResponseWriter, r *http.Request) Work {
	return Work{w, r}
}

func NewConcurrentProxy(addr, port string, anony, debug bool, maxGoroutines int) *ConcurrentProxy {
	proxy := &ConcurrentProxy{
		addr:        addr,
		port:        port,
		isAnonymous: anony,
		debug:       debug,
		works:       make(chan Work),
	}
	return proxy
}

func StartConcurrentProxy(addr, port string, anony, debug bool, maxGoroutines int) {
	proxy := NewConcurrentProxy(addr, port, anony, debug, maxGoroutines)
	defer proxy.Shutdown()
	log.Printf("Proxy is running on #{proxy.addr}:#{proxy.port}")
	log.Fatalln(http.ListenAndServe(proxy.addr+":"+proxy.port, proxy))
}
