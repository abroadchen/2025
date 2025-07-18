/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import (
	"fmt"
	"net/http"
)

func body(w http.ResponseWriter, r *http.Request) {
	len := r.ContentLength
	body := make([]byte, len)
	r.Body.Read(body)
	fmt.Fprintln(w, string(body))
	h := r.Header
	fmt.Fprintln(w, h)
}

func main() {
	http.HandleFunc("/", body)
	http.ListenAndServe(":8080", nil)
}
