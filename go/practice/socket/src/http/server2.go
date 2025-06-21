package main

import (
	"fmt"
	"net/http"
	"time"
)

type msg string

func (m msg) ServeHTTP(resp http.ResponseWriter, r *http.Request) {
	resp.Header().Add("Content-Type", "text/html; charset=utf-8")
	resp.WriteHeader(http.StatusOK)
	fmt.Fprint(resp, m)
}

func main() {
	msgHandler := msg("")
	//server := http.Server{Addr: ":8080", Handler: msgHandler}
	server := http.Server{
		Addr:         ":8080",
		Handler:      msgHandler,
		ReadTimeout:  5 * time.Second,
		WriteTimeout: 5 * time.Second,
	}
	server.ListenAndServe()

	mux := http.NewServeMux()
	hello := func(resp http.ResponseWriter, req *http.Request) {
		resp.Header().Add("Content-Type", "text/html; charset=utf-8")
		resp.WriteHeader(http.StatusOK)
		fmt.Fprint(resp, "<h1>Hello World!</h1>")
	}
	goodbye := func(resp http.ResponseWriter, req *http.Request) {
		resp.Header().Add("Content-Type", "text/html; charset=utf-8")
		resp.WriteHeader(http.StatusOK)
		fmt.Fprint(resp, "<h1>Goodbye World!</h1>")
	}
	mux.HandleFunc("/hello", hello)
	mux.HandleFunc("/goodbye", goodbye)
	http.ListenAndServe(":8080", mux)
}
