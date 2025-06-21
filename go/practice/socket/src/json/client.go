package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"net/http"
)

func main() {
	var param string
	fmt.Println("Currency>")
	_, err := fmt.Scanf("%s", &param)
	buf := new(bytes.Buffer)
	currRequest := &CurrencyRequest{Get: param}
	err = json.NewEncoder(buf).Encode(currRequest)
	if err != nil {
		fmt.Println(err)
		return
	}
	client := &http.Client{}
	req, err := http.NewRequest("POST", "http://127.0.0.1:8080/currency", buf)
	if err != nil {
		fmt.Println(err)
		return
	}
	resp, err := client.Do(req)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer resp.Body.Close()

	var currencies []Currency
	err = json.NewDecoder(resp.Body).Decode(&currencies)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(currencies)
}
