/*
Package cookie

	@author: June
	@since: 2025/7/18
	@desc:
*/
package cookie

import (
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
)

func HandleRequest(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	body, err := ioutil.ReadAll(r.Body)
	r.Body.Close()

	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("body:", string(body))
	fmt.Printf("%+v\n", r)
	fmt.Printf("Request: Header %+v\n", r.Header)
	fmt.Printf("cookies %+v\n", r.Cookies())

	cookid, err := r.Cookie("userId")
	if err != nil {
		fmt.Println(cookid.Name, cookid.Value)
	}

	if len(r.Form["username"]) > 0 {
		username := r.Form["username"][0]
		fmt.Println(username)
	}

	if len(r.Form["password"]) > 0 {
		password := r.Form["password"][0]
		fmt.Println(password)
	}

	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Access-Control-Allow-Headers", "Content-Type")
	io.WriteString(w, "login success")

}

func main() {
	http.HandleFunc("/login", HandleRequest)
	err := http.ListenAndServe(":2000", nil)
	if err != nil {
		fmt.Println(err)
	}
}
