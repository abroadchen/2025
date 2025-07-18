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

type xHandler struct{}

func (xHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "hello")
}

type yHandler struct{}

func (yHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "world")
}

func main() {
	hello := xHandler{}
	world := yHandler{}

	server := http.Server{
		Addr: ":8080",
	}
	http.Handle("/hello", hello)
	http.Handle("/world", world)

	server.ListenAndServe()
}
