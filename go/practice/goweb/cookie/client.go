/*
Package cookie

	@author: June
	@since: 2025/7/18
	@desc:
*/
package cookie

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
)

func main() {
	urlStr := "http://localhost:2000/login"
	client := http.Client{}
	param := url.Values{
		"username": {"admin"},
	}

	requestBody := bytes.NewBufferString(param.Encode())
	request, err := http.NewRequest("POST", urlStr, requestBody)
	if err != nil {
		fmt.Println(err)
	}

	cookId := &http.Cookie{
		Name:  "userId",
		Value: "123",
	}
	cookName := &http.Cookie{
		Name:  "name",
		Value: "admin",
	}
	request.AddCookie(cookId)
	request.AddCookie(cookName)
	request.Header.Set("Content-Type", "application/x-www-form-urlencoded")
	response, err := client.Do(request)
	if err != nil {
		fmt.Println(err)
	}
	defer response.Body.Close()

	if response.StatusCode == 200 {
		body, _ := ioutil.ReadAll(response.Body)
		fmt.Println(string(body))
	}

	fmt.Printf("response: %+v\n", response)
	fmt.Printf("response.Header: %+v\n", response.Header)
	fmt.Printf("response.Cookies: %+v\n", response.Cookies())
	fmt.Printf("resquest.Header: %+v\n", request.Header)
	fmt.Printf("request.Cookies: %+v\n", request.Cookies())
}
