/*
Package httppost

	@author: June
	@since: 2025/7/18
	@desc:
*/
package httppost

import (
	"bytes"
	"fmt"
	"io"
	"net/http"
	"net/url"
)

func main() {
	urlStr := "http://localhost:2001/login"
	param := url.Values{
		"username": []string{"admin"},
		"password": []string{"admin"},
	}
	requestBody := bytes.NewBufferString(param.Encode())
	resp, err := http.Post(urlStr, "application/x-www-form-urlencoded", requestBody)

	if err != nil {
		fmt.Println(err)
	}
	defer resp.Body.Close()

	if resp.StatusCode == 200 {
		body, _ := io.ReadAll(resp.Body)
		fmt.Println(string(body))
	}

	fmt.Printf("response: %+v\n", resp)
	fmt.Printf("response.Header: %+v\n", resp.Header)
	fmt.Printf("response.Cookies: %+v\n", resp.Cookies())
}
