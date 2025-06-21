package main

import (
	"fmt"
	"net/http"
	"os"
)

func CheckStatusOK(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusOK)
	fmt.Fprintln(w, `Fine!`)
}

func StatusNotFound(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintln(w, "serving: %s\n", r.URL.Path)
	fmt.Fprintln(w, "served: %s\n", r.Host)
}

func MyHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintln(w, "Serving:%s\n", r.URL.Path)
	fmt.Fprintln(w, "served: %s\n", r.Host)
}

func main() {
	PORT := ""
	argument := os.Args
	if len(argument) == 1 {
		fmt.Println("Using Default port number", PORT)
	} else {
		PORT = ":" + argument[1]
	}
	http.HandleFunc("/CheckStatusOK", CheckStatusOK)
	http.HandleFunc("/StatusNotFound", StatusNotFound)
	http.HandleFunc("/", MyHandler)
	err := http.ListenAndServe(PORT, nil)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
