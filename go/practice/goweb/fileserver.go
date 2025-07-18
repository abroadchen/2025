/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import "net/http"

func main() {
	err := http.ListenAndServe(":8080", http.FileServer(http.Dir(".")))
	if err != nil {
		panic(err)
	}
}
