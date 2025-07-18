/*
Package chain_handler

	@author: June
	@since: 2025/7/18
	@desc:
*/
package chain_handler

import (
	"fmt"
	"net/http"
)

func setCookie(w http.ResponseWriter, r *http.Request) {
	c1 := http.Cookie{
		Name:     "cookie1",
		Value:    "value1",
		HttpOnly: true,
	}
	c2 := http.Cookie{
		Name:     "cookie2",
		Value:    "value2",
		HttpOnly: true,
	}
	http.SetCookie(w, &c1)
	http.SetCookie(w, &c2)
}

func getCookie(w http.ResponseWriter, r *http.Request) {
	h := r.Header["Cookie"]
	c1, _ := r.Cookie("cookie1")
	cs := r.Cookies()

	fmt.Fprintln(w, h)
	fmt.Fprintln(w, c1)
	fmt.Fprintln(w, cs)
}

func main() {
	http.HandleFunc("/setCookie", setCookie)
	http.HandleFunc("/getCookie", getCookie)
	http.ListenAndServe(":8080", nil)
}
