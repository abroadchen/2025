package main

import (
	"io"
	"log"
	"net/http"
)

func HelloServer(w http.ResponseWriter, req *http.Request) {
	io.WriteString(w, "Hello World")
}
func main() {
	http.HandleFunc("/", HelloServer)
	err := http.ListenAndServeTLS("0.0.0.0:443", "server.crt", "server.key", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}
