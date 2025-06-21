package main

import (
	"fmt"
	"net/http"
	"net/http/pprof"
	"os"
)

func main() {
	PORT := ""
	arguments := os.Args
	if len(arguments) == 1 {
		fmt.Println("usage default port number:", PORT)
	} else {
		PORT = ":" + arguments[1]
		fmt.Println("usage port number:", PORT)
	}

	r := http.NewServeMux()
	r.HandleFunc("/time", timeHandler)
	r.HandleFunc("/", myHandler)

	r.HandleFunc("debug/pprof/", pprof.Index)
	r.HandleFunc("debug/pprof/cmdline", pprof.Cmdline)
	r.HandleFunc("debug/pprof/profile", pprof.Profile)
	r.HandleFunc("debug/pprof/symbol", pprof.Symbol)
	r.HandleFunc("debug/pprof/trace", pprof.Trace)
}
