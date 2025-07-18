/*
Package goweb

	@author: June
	@since: 2025/7/18
	@desc:
*/
package goweb

import (
	"fmt"
	"log"
	"net/http"
	"strings"
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Write([]byte("解析参数"))
		fmt.Println("---------------------")
		fmt.Println(r.Form)
		fmt.Println("path:", r.URL.Path)
		fmt.Println("scheme:", r.URL.Scheme)
		fmt.Println(r.Form["url_long"])
		for k, v := range r.Form {
			fmt.Println("key:", k)
			fmt.Println("val:", strings.Join(v, ""))
		}
		fmt.Fprintf(w, "输出到客户端")
	})
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal(err)
	}
}
