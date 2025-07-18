/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import "net/http"

func writeExample(w http.ResponseWriter, r *http.Request) {
	str := `<!DOCTYPE html>`
	w.Write([]byte(str))
}

func main() {
	http.HandleFunc("/", writeExample)
	http.ListenAndServe(":8080", nil)
}
