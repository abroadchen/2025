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

type xHandler struct{}

func (xHandler *xHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello World")
}

/*
logHandler

	@Description: 中间件
	@param h
	@return http.Handler
*/
func logHandler(h http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		fmt.Printf("Handler called: %T\n", h)
		h.ServeHTTP(w, r)
	})
}

func main() {
	handler := &xHandler{}
	http.Handle("/", logHandler(handler))
	http.ListenAndServe(":8080", nil)
}
