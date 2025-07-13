package websocket

import (
	"fmt"
	"net/http"
)

func main() {
	router := mux.NewRouter()
	go h.run()
	router.HandleFunc("/ws", myws)
	if err := http.ListenAndServe(":8080", router); err != nil {
		fmt.Println(err)
	}
}
