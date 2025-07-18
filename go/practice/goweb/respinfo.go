/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import (
	"fmt"
	"io"
	"net/http"
)

func main() {
	urlStr := ""
	response, err := http.Get(urlStr)
	if err != nil {
		fmt.Println(err)
	}
	defer response.Body.Close()

	if response.StatusCode == 200 {
		body, err := io.ReadAll(response.Body)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(string(body))
	}

	fmt.Println("--------------------")
	fmt.Printf("response: %+v\n", response)
	fmt.Println("--------------------")
	fmt.Printf("response.Body: %+v\n", response.Body)
	fmt.Printf("response.Header: %+v\n", response.Header)
	fmt.Printf("response.StatusCode: %+v\n", response.StatusCode)
	fmt.Printf("response.Status: %+v\n", response.Status)
	fmt.Printf("response.Request: %+v\n", response.Request)
	fmt.Printf("response.Cookies: %+v\n", response.Cookies())
}
