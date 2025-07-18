/*
Package httppost

	@author: June
	@since: 2025/7/18
	@desc:
*/
package httppost

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
)

func main() {
	resp, err := http.PostForm("http://localhost:2001/login", url.Values{
		"username": []string{"admin"},
		"password": []string{"admin"},
	})
	if err != nil {
		fmt.Println(err)
	}
	defer resp.Body.Close()

	if resp.StatusCode == 200 {
		body, _ := ioutil.ReadAll(resp.Body)
		fmt.Println(string(body))
	}

	fmt.Printf("response: %+v\n", resp)
	fmt.Printf("response.Header: %+v\n", resp.Header)
	fmt.Printf("response.Cookies: %+v\n", resp.Cookies())
}
