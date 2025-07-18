/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import (
	"fmt"
	"html/template"
	"io"
	"net/http"
)

func process(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	fmt.Fprintln(w, r.PostForm)
}

func upload(w http.ResponseWriter, r *http.Request) {
	if r.Method == "GET" {
		t, _ := template.ParseFiles("upload.gtpl")
		t.Execute(w, nil)
	} else {
		file, _, err := r.FormFile("uploaded")
		if err == nil {
			data, _ := io.ReadAll(file)
			if err == nil {
				fmt.Fprintln(w, string(data))
			}
		}
	}
}

func main() {
	http.HandleFunc("/form", process)
	http.HandleFunc("/upload", upload)
	http.ListenAndServe(":8080", nil)
}
