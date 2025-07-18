/*
Package httppost

	@author: June
	@since: 2025/7/18
	@desc:
*/
package httppost

import (
	"fmt"
	"io"
	"net/http"
)

func main() {
	server := http.NewServeMux()
	server.HandleFunc("/login", login)
	http.ListenAndServe(":8080", server)
}

func login(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	body, err := io.ReadAll(r.Body)
	r.Body.Close()
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("body:", string(body))
	fmt.Printf("%+v\n", r)
	fmt.Printf("%+v\n", r.Header)
	fmt.Printf("%+v\n", r.Header["Content-Type"])
	fmt.Printf("%+v\n", r.Cookies())

	if len(r.Form["username"]) > 0 {
		username := r.Form["username"][0]
		fmt.Println("username:", username)
	}

	if len(r.Form["password"]) > 0 {
		password := r.Form["password"][0]
		fmt.Println("password:", password)
	}

	io.WriteString(w, "登录成功")
}
