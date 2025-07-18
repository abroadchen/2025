/*
Package chain_handler

	@author: June
	@since: 2025/7/18
	@desc:
*/
package chain_handler

import (
	"fmt"
	"net/http"
)

type xxHandler struct{}

func (xxHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "hello")
}

func logHandler(h http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		fmt.Printf("Handler called: %v\n", h)
		h.ServeHTTP(w, r)
	})
}

func main() {
	handler := &xxHandler{}
	http.Handle("/", logHandler(handler))
	http.ListenAndServe(":8080", nil)
}
