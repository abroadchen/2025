/*
Package chain_handler

	@author: June
	@since: 2025/7/18
	@desc:
*/
package chain_handler

import (
	"html/template"
	"net/http"
)

func xssAttackExample(w http.ResponseWriter, r *http.Request) {
	t := template.Must(template.ParseFiles("templates/xss"))
	if r.Method == "GET" {
		t.Execute(w, nil)
	} else {
		t.Execute(w, template.HTML(r.FormValue("content")))
	}
}

func main() {
	http.HandleFunc("/xss", xssAttackExample)
	http.ListenAndServe(":8080", nil)
}
