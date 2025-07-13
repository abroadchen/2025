package etcd

import (
	"fmt"
	"io"
	"net/http"
	"net/http/httputil"
	"net/url"
	"strings"
	"time"
)

var i int

func NewServerlistX(urls []*url.URL) *httputil.ReverseProxy {
	direct := func(req *http.Request) {
		myurl := urls[i%len(urls)]
		req.URL.Scheme = myurl.Scheme
		req.URL.Host = myurl.Host
		req.URL.Path = myurl.Path
		i++
	}
	return &httputil.ReverseProxy{Director: direct}
}

func GetclientFromETCD() []string {

	var myetcd safeETCD.SafeETCD
	myetcd = safeETCD.NewETCDGO([]string{"http://127.0.0.1:2379"}, []string{"crc64", "sha256"}, "123", "mytemp")
	serverlistkey := "Serverlist"
	valueip := "127.0.0.1:9000"
	getstr := myetcd.GetString(serverlistkey)
	if getstr == "" {
		//myetcd.SetString(serverlistkey, getstr)
		return []string{}
	} else {
		if !strings.Contains(getstr, "#$#") {
			return []string{getstr}
		} else {
			getlist := strings.Split(getstr, "#$#")
			return getlist
		}
	}
	//} else if !strings.Contains(getstr, "#$#") {
	//	if getstr != valueip {
	//		getstr += "#$#"
	//		getstr += valueip
	//		myetcd.SetString(serverlistkey, getstr)
	//	} else {
	//
	//	}
	//} else {
	//	getlist := strings.Split(getstr, "#$#")
	//	var isin bool = false
	//	for i := 0; i < len(getlist); i++ {
	//		if getlist[i] == valueip {
	//			isin = true
	//			break
	//		}
	//	}
	//	if !isin {
	//		getstr += "#$#"
	//		getstr += valueip
	//		myetcd.SetString(serverlistkey, getstr)
	//	} else {
	//
	//	}
	//}

	//proxy := NewServerlistX([]*url.URL{
	//	{
	//		Scheme: "http",
	//		Host:   "127.0.0.1:8081",
	//	},
	//	{
	//		Scheme: "http",
	//		Host:   "127.0.0.1:8082",
	//	},
	//	{
	//		Scheme: "http",
	//		Host:   "127.0.0.1:8083",
	//	},
	//})
	//http.ListenAndServe(":9000", proxy)
}

func checkurl(url string) bool {
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println(err)
		return false
	}
	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		fmt.Println(err)
		return false
	}
	fmt.Println(string(body))
	return true
}

func main() {
	for {
		time.Sleep(time.Minute)
		clientlist := GetclientFromETCD()
		newclientlist := []string{}
		for i := 0; i < len(clientlist); i++ {
			if checkurl("http://" + clientlist[i]) {
				newclientlist = append(newclientlist, clientlist[i])
			}
		}

		var clientstr string
		if len(newclientlist) == 0 {
			clientstr = ""
		} else if len(newclientlist) == 1 {
			clientstr = newclientlist[0]
		} else {
			clientstr = newclientlist[0]
			for i := 0; i < len(newclientlist); i++ {
				clientstr += "#$#"
				clientstr += newclientlist[i]
			}
		}

		var myetcd safeETCD.SafeETCD
		myetcd = safeETCD.NewETCDGO([]string{"http://127.0.0.1:2379"}, []string{"crc64", "sha256"}, "123", "mytemp")
		myetcd.SetString("Clientlist", clientstr)

	}
}
