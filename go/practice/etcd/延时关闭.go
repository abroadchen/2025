package etcd

import (
	"context"
	"fmt"
	"net/http"
	"time"
)

func StartServer(ctx context.Context) {

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		body, _ := json.Marshal(map[string]string{"addr": r.RemoteAddr})
		fmt.Fprint(w, string(body))
		fmt.Println("8001")
		w.Write([]byte(body))
	})
	go http.ListenAndServe(":8081", nil)

	for {
		select {
		case <-ctx.Done():
			return
		}
	}
}

func StopServer(cancel context.CancelFunc) {
	cancel()
}

func main() {
	//go StartServer()
	//time.Sleep(10 * time.Second)
	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)
	go StartServer(ctx)
	time.Sleep(20 * time.Second)
	cancel()
}
