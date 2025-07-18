/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import (
	"bytes"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"strings"
)

func main11() {
	urlStr := ""
	client := http.Client{}
	param := &url.Values{
		"theCityName": {"苏州"},
	}
	requestBody := bytes.NewBufferString(param.Encode())
	resp, err := client.Post(urlStr, "application/x-www-form-urlencoded", requestBody)
	if err != nil {
		fmt.Println(err)
	}
	defer resp.Body.Close()

	if resp.StatusCode == 200 {
		body, _ := io.ReadAll(resp.Body)
		fmt.Println(string(body))
	}
	fmt.Printf("%+v", resp)
}

func main() {
	resp, err := http.Post("", "application/x-www-form-urlencoded", strings.NewReader("theCityName=苏州"))
	if err != nil {
		fmt.Println(err)
	}
	defer resp.Body.Close()
	body, _ := io.ReadAll(resp.Body)
	fmt.Println(string(body))
}
