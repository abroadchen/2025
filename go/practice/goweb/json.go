/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import (
	"encoding/json"
	"net/http"
)

type Post struct {
	User    string
	Threads []string
}

func jsonExample(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	post := Post{
		User:    "john",
		Threads: []string{"", ""},
	}
	data, _ := json.Marshal(post)
	w.Write(data)
}

func main() {
	http.HandleFunc("/", jsonExample)
	http.ListenAndServe(":8080", nil)
}
