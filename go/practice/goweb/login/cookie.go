/*
Package login

	@author: June
	@since: 2025/7/18
	@desc:
*/
package login

import (
	"fmt"
	"net/http"
)

func main() {
	http.HandleFunc("/setcookie", SetCookie)
	http.HandleFunc("/getcookie", GetCookie)
	http.ListenAndServe(":8080", nil)
}

func SetCookie(w http.ResponseWriter, r *http.Request) {
	cookie := http.Cookie{
		Name:  "name",
		Value: "",
	}
	http.SetCookie(w, &cookie)
	w.Write([]byte("ok"))
}

func GetCookie(w http.ResponseWriter, r *http.Request) {
	cookie, err := r.Cookie("name")
	if err != nil {
		
	}
	fmt.Fprintln(w, cookie)
}
