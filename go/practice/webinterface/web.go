package webinterface

import (
	"fmt"
	"net/http"
)

func WordFind(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	for k, v := range r.Form {
		fmt.Println(k, v)
	}
	fmt.Fprintln(w, "")
}

func main() {
	http.HandleFunc("/word/find", WordFind)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		fmt.Println(err)
	}

}
