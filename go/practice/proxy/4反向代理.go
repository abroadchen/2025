package proxy

import (
	"github.com/gogo/protobuf/protoc-gen-gogo/testdata/imports/fmt"
	"net/http"
	"net/http/httputil"
	"net/url"
)

func NewMultipleHostsReversePorxy(targets []*url.URL) *httputil.ReverseProxy {
	director := func(req *http.Request) {
		target := targets[rand.Int()%len(targets)]
		fmt.Println(target)
		req.URL.Scheme = target.Scheme
		req.URL.Host = target.Host
		req.URL.Path = target.Path
	}
	return &httputil.ReverseProxy{Director: director}
}

func main() {
	proxy := NewMultipleHostsReversePorxy([]*url.URL{
		{
			Scheme: "http",
			Host:   "127.0.0.1:8091",
		},
		{
			Scheme: "http",
			Host:   "127.0.0.1:8092",
		},
	})
	log.Fatal(http.ListenAndServe(":8090", proxy))
}
