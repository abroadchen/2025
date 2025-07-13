package cert

import (
	"io"
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		io.WriteString(w, "hello world")
	})
	log.Printf("Starting https server at port 8080")
	err := http.ListenAndServeTLS(":8080", "cert.pem", "key.pem", nil)
	log.Fatal(err)
}
