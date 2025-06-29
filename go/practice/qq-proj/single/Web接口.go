package single

import (
	"fmt"
	"net/http"
)

func WordFind(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	var word string
	var email string
	for k, v := range r.Form {
		if k == "word" {
			word = v[0]
		}
	}
	if word == "" {
		fmt.Println("<UNK>")
	} else {
		fmt.Fprintf(w, "业务已经开启 完成了给你发邮件")
	}
}

func main() {
	http.HandleFunc("/WordFind", WordFind)
	err := http.ListenAndServe(":9090", nil)
	if err != nil {
		fmt.Println("http.ListenAndServe", err)
	}

}
