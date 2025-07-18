/*
Package chain_handler

	@author: June
	@since: 2025/7/18
	@desc:
*/
package chain_handler

import (
	"fmt"
	"github.com/julienschmidt/httprouter"
	"net/http"
)

func hello2(w http.ResponseWriter, r *http.Request, p httprouter.Params) {
	fmt.Fprintln(w, "hello2")
}

func main() {
	mux := httprouter.New()
	mux.GET("/hello/:name", hello2)

	server := http.Server{
		Addr:    ":8080",
		Handler: mux,
	}
	server.ListenAndServe()
}
