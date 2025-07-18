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

func statusCodeExample(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(501)
	fmt.Fprintln(w, "No such endpoint")
}

func headerExample(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Location", "https://qq.com")
	w.WriteHeader(302)
}

func main() {
	http.HandleFunc("/statusCode", statusCodeExample)
	http.HandleFunc("/redirect", headerExample)
	http.ListenAndServe(":8080", nil)
}
