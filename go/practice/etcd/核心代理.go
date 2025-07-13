package etcd

import (
	"fmt"
	"net/http"
	"net/url"
	"time"
)

func StartHttpServer(ip string) *http.Server {
	proxy := NewServerlistX([]*url.URL{
		{
			Scheme: "http",
			Host:   ip,
		},
	})
	srv := &http.Server{
		Addr:    ":8080",
		Handler: proxy,
	}
	go func() {
		if err := srv.ListenAndServe(); err != nil {
			fmt.Println(err)
			return
		}
	}()
	return srv
}

func main() {
	proxylist := GetProxyFromETCD()
	srv := StartHttpServer(proxylist[0])

	for {
		proxylist := GetclientFromETCD()
		newproxylist := []string{}
		for i := 0; i < len(proxylist); i++ {
			if checkurl("http://" + proxylist[i]) {
				newproxylist = append(newproxylist, proxylist[i])
			}
		}

		var clientstr string
		if len(newproxylist) == 0 {
			clientstr = ""
		} else if len(newproxylist) == 1 {
			clientstr = newproxylist[0]
		} else {
			clientstr = newproxylist[0]
			for i := 0; i < len(newproxylist); i++ {
				clientstr += "#$#"
				clientstr += newproxylist[i]
			}
		}

		var myetcd safeETCD.SafeETCD
		myetcd = safeETCD.NewETCDGO([]string{"http://127.0.0.1:2379"}, []string{"crc64", "sha256"}, "123", "mytemp")
		myetcd.SetString("Clientlist", clientstr)
		if len(newproxylist) == 0 {
			fmt.Println("服务器崩溃")
			return
		}
		if len(proxylist) != len(newproxylist) {
			srv.Shutdown(nil)
			srv.Close()
			srv = StartHttpServer(proxylist[0])
		}
	}

}
