package proxy

import (
	"fmt"
	"net/http"
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		body, _ := json.Marshal(map[string]string{
			"addr": r.RemoteAddr,
		})
		fmt.Println(string(body))
		w.Write(body)
	})
	http.ListenAndServe(":8092", nil)
}
