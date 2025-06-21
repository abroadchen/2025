package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"os"
)

var currencies = Load("./data.csv")

func currs(resp http.ResponseWriter, req *http.Request) {
	var currRequest CurrencyRequest
	dec := json.NewDecoder(req.Body)
	if err := dec.Decode(&currRequest); err != nil {
		resp.WriteHeader(http.StatusBadRequest)
		fmt.Println(err)
		return
	}

	result := Find(currencies, currRequest.Get)
	enc := json.NewEncoder(resp)
	if err := enc.Encode(result); err != nil {
		fmt.Println(err)
		resp.WriteHeader(http.StatusInternalServerError)
		return
	}
}

func gui(resp http.ResponseWriter, req *http.Request) {
	file, err := os.Open("./currency.html")
	if err != nil {
		resp.WriteHeader(http.StatusInternalServerError)
		fmt.Println(err)
		return
	}
	io.Copy(resp, file)
}

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", gui)
	mux.HandleFunc("/currency", currs)
	if err := http.ListenAndServe(":8080", mux); err != nil {
		fmt.Println(err)
	}
}
