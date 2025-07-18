/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import (
	"log"
	"net/http"
	"os"
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		content, _ := os.ReadFile("html/index.html")
		w.Write(content)
	})
	log.Fatal(http.ListenAndServe(":8080", nil))
}
