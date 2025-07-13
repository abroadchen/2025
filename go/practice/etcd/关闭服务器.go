package etcd

import (
	"net"
	"net/http"
	"time"
)

//func StartHttpServer() *http.Server {
//	srv := &http.Server{Addr: ":8080"}
//	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
//		io.WriteString(w, "hello 8080")
//	})
//	go func() {
//		if err := srv.ListenAndServe(); err != nil && err != http.ErrServerClosed {
//			log.Fatalf("listen: %s\n", err)
//		}
//	}()
//	return srv
//}
//
//func main() {
//	srv := StartHttpServer()
//	time.Sleep(time.Second * 10)
//	if err := srv.Shutdown(context.Background()); err != nil {
//		log.Fatal(err)
//	}
//	srv.Close()
//}

type HTTP struct {
	listener net.Listener
}

func (h *HTTP) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte("hello "))
}

func mainlx() {
	l, _ := net.Listen("tcp", ":8081")
	h := new(HTTP)
	h.listener = l
	go func() {
		http.Serve(h.listener, h)
	}()
	time.Sleep(time.Second * 10)
	h.listener.Close()
}

func main() {
	mainlx()
	time.Sleep(time.Second * 10)
	mainlx()
}
