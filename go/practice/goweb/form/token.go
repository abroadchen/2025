/*
Package form

	@author: June
	@since: 2025/7/18
	@desc:
*/
package form

import (
	"crypto/md5"
	"fmt"
	"html/template"
	"io"
	"log"
	"net/http"
	"strconv"
	"time"
)

func login5(w http.ResponseWriter, r *http.Request) {
	fmt.Println("method:", r.Method)
	if r.Method == "GET" {
		crutime := time.Now().Unix()
		h := md5.New()
		io.WriteString(h, strconv.FormatInt(crutime, 10))
		token := fmt.Sprintf("%x", h.Sum(nil))
		fmt.Println("token:", token)
		t, _ := template.ParseFiles("test.gtpl")
		t.Execute(w, token)
	} else {
		r.ParseForm()
		token := r.Form.Get("token")
		fmt.Println(token)
		if token != "" {
			fmt.Println("token:", token)
		} else {
			fmt.Println("token is empty")
		}
		if len(r.Form["username"]) > 1 {
			fmt.Println("username length:", len(r.Form["username"][0]))
		}

		fmt.Println("username:", template.HTMLEscapeString(r.Form.Get("username")))
		fmt.Println("password:", template.HTMLEscapeString(r.Form.Get("password")))
		template.HTMLEscape(w, []byte("username"))
	}
}

func main() {
	http.HandleFunc("/login", login5)
	err := http.ListenAndServe(":9090", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}
