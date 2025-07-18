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
	requestUrl := ""
	response, err := http.Get(requestUrl)
	if err != nil {
		fmt.Println(err)
	}

	b, _ := io.ReadAll(response.Body)
	fmt.Println(string(b))

	defer response.Body.Close()
	fmt.Println(response.Body)
}
