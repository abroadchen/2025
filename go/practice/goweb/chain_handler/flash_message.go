/*
Package chain_handler

	@author: June
	@since: 2025/7/18
	@desc:
*/
package chain_handler

import (
	"encoding/base64"
	"fmt"
	"net/http"
	"time"
)

func setMessage(w http.ResponseWriter, r *http.Request) {
	msg := []byte("Hello World")
	cookie := http.Cookie{
		Name:  "cookie",
		Value: base64.URLEncoding.EncodeToString(msg),
	}
	http.SetCookie(w, &cookie)
}

func getMessage(w http.ResponseWriter, r *http.Request) {
	cookie, err := r.Cookie("cookie")
	if err != nil {
		fmt.Fprintln(w, "No flash message found in cookie")
	} else {
		delCookie := http.Cookie{
			Name:    "cookie",
			MaxAge:  -1,
			Expires: time.Unix(1, 0),
		}
		http.SetCookie(w, &delCookie)
		message, _ := base64.URLEncoding.DecodeString(cookie.Value)
		fmt.Fprintln(w, string(message))
	}
}

func main() {
	http.HandleFunc("/setMessage", setMessage)
	http.HandleFunc("/getMessage", getMessage)
	http.ListenAndServe(":8080", nil)
}
