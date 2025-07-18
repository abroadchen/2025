/*
Package chain_handler

	@author: June
	@since: 2025/7/18
	@desc:
*/
package chain_handler

import "net/http"

func main() {
	server := http.Server{
		Addr:    ":8080",
		Handler: nil,
	}
	server.ListenAndServeTLS("server.crt", "server.key")
}
