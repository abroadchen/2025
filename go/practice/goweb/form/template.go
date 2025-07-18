/*
Package form

	@author: June
	@since: 2025/7/18
	@desc:
*/
package form

import (
	"fmt"
	"html/template"
	"net/http"
)

func login2(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	username := r.Form.Get("username")
	fmt.Println("username:", template.HTMLEscapeString(username))
	fmt.Println("password:", template.HTMLEscapeString(r.Form.Get("password")))
	template.HTMLEscape(w, []byte("username")) //输出到客户端
}

func login3(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	username := r.Form.Get("username")
	fmt.Println(username)

	t, err := template.New("foo").Parse(`{{define "T"}}Hello, {{.}}!{{end}}`)
	err = t.ExecuteTemplate(w, "T", template.HTML(username))
	if err != nil {
		fmt.Println(err)
	}
}

func main() {
	http.HandleFunc("/login", login2)
	http.HandleFunc("/login3", login3)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		fmt.Println(err)
	}
}
