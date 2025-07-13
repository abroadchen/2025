package etcd

import (
	"fmt"
	"net"
	"net/http"
	"net/url"
	"time"
)

func CheckHost(url string) bool {
	url = "http://" + url
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println("1", err)
		return false
	}
	return true
}

var ishost = false
var i int = 0 //负载均衡
var valueip string = "127.0.0.1:8001"
var slaveserver *HTTP //客户机

func Monitor() {
	for {
		var myetcd safeETCD.SafeETCD
		myetcd = safeETCD.NewETCDGO([]string{"http://127.0.0.1:2379"}, []string{"crc64", "sha256"}, "123", "mytemp")
		serverlistkey := "hostServer"
		valueip := "127.0.0.1:8001"
		getstr := myetcd.GetString(serverlistkey)
		time.Sleep(time.Second * 10)

		if CheckHost(getstr) == false {
			fmt.Println("大哥空缺")
			if ishost == true {
				fmt.Println("已经是大哥")
				continue
			} else {
				x := rand.Int() % 30
				time.Sleep(time.Duration(x) * time.Second)

				dage := myetcd.GetString(serverlistkey)
				if dage != getstr && dage != valueip {
					continue
				}
				ishost = true
				myetcd.SetString(serverlistkey, valueip)
				slaveserver.listener.Close()

				var slavelist []string
			AAA:
				slavelist = GetServerlistFromETCD()
				if len(slavelist) == 0 {
					time.Sleep(time.Second * 10)
					goto AAA
				}
				newslavelist := []string{}
				for i = 0; i < len(slavelist); i++ {
					if slavelist[i] != valueip {
						newslavelist = append(newslavelist, slavelist[i])
					}
				}

				var clientstr string
				if len(newslavelist) == 0 {
					clientstr = ""
				} else if len(newslavelist) == 1 {
					clientstr = newslavelist[0]
				} else {
					clientstr = newslavelist[0]
					for i := 0; i < len(newslavelist); i++ {
						clientstr += "#$#"
						clientstr += newslavelist[i]
					}
				}

				var myetcd safeETCD.SafeETCD
				myetcd = safeETCD.NewETCDGO([]string{"http://127.0.0.1:2379"}, []string{"crc64", "sha256"}, "123", "mytemp")
				myetcd.SetString(slavelistkey, clientstr)

				proxy := StartHttpServer(newslavelist)
				for {
					if ishost {
						time.Sleep(time.Second * 10)
						fmt.Println("大哥活着", proxy)
					}

				}

			}
		} else {
			if ishost {
				fmt.Println("安心做大哥")
			} else {
				fmt.Println("安心做小第")
			}
		}

		//if getstr == "" || CheckHost(getstr) == false {
		//	myetcd.SetString(serverlistkey, valueip)
		//	ishost = true
		//	slaveserver.listener.Close()
		//	var slavelist []string
		//AAA:
		//	slavelist = GetServerlistFromETCD()
		//	if len(slavelist) == 0 {
		//		time.Sleep(time.Second * 10)
		//		goto AAA
		//	}
		//	newslavelist := []string{}
		//	for i = 0; i < len(slavelist); i++ {
		//		if slavelist[i] != valueip {
		//			newslavelist = append(newslavelist, slavelist[i])
		//		}
		//	}
		//
		//	var clientstr string
		//	if len(newslavelist) == 0 {
		//		clientstr = ""
		//	} else if len(newslavelist) == 1 {
		//		clientstr = newslavelist[0]
		//	} else {
		//		clientstr = newslavelist[0]
		//		for i := 0; i < len(newslavelist); i++ {
		//			clientstr += "#$#"
		//			clientstr += newslavelist[i]
		//		}
		//	}
		//
		//	var myetcd safeETCD.SafeETCD
		//	myetcd = safeETCD.NewETCDGO([]string{"http://127.0.0.1:2379"}, []string{"crc64", "sha256"}, "123", "mytemp")
		//	myetcd.SetString(slavelistkey, clientstr)
		//
		//	proxy := StartHttpServer(newslavelist)
		//	for {
		//		if ishost {
		//			time.Sleep(time.Second * 10)
		//			fmt.Println("大哥活着", proxy)
		//		}
		//
		//	}
		//
		//	//for {
		//	//	if ishost {
		//	//		time.Sleep(time.Second * 5)
		//	//		fmt.Println("我是大哥", valueip)
		//	//	} else {
		//	//		return
		//	//	}
		//	//}
		//} else {
		//	if ishost {
		//		fmt.Println("安心做大哥")
		//	} else {
		//		fmt.Println("安心做小第")
		//	}
		//}
	}
}

func main() {
	//ishost := true
	//if ishost {
	//
	//} else {
	//
	//}
	go Monitor()
	var myetcd safeETCD.SafeETCD
	myetcd = safeETCD.NewETCDGO([]string{"http://127.0.0.1:2379"}, []string{"crc64", "sha256"}, "123", "mytemp")
	serverlistkey := "hostServer"
	valueip := "127.0.0.1:8001"
	getstr := myetcd.GetString(serverlistkey)

	if getstr == "" {
		myetcd.SetString(serverlistkey, valueip)
		ishost = true
		var slavelist []string
	AAA:
		slavelist = GetServerlistFromETCD()
		if len(slavelist) == 0 {
			time.Sleep(time.Second * 10)
			goto AAA
		}
		proxy := StartHttpServer(slavelist)
		for {
			if ishost {
				time.Sleep(time.Second * 10)
				fmt.Println("大哥活着", proxy)
			}

		}
		//for {
		//	if ishost {
		//		time.Sleep(time.Second * 5)
		//		fmt.Println("我是大哥", valueip)
		//	} else {
		//		return
		//	}
		//}
	} else if getstr == valueip {
		ishost = true
		var slavelist []string
	AAB:
		slavelist = GetServerlistFromETCD()
		if len(slavelist) == 0 {
			time.Sleep(time.Second * 10)
			goto AAB
		}
		proxy := StartHttpServer(slavelist)
		for {
			if ishost {
				time.Sleep(time.Second * 10)
				fmt.Println("大哥活着", proxy)
			}

		}
	} else if getstr != valueip {

		ishost = false
		RigsterETCD(valueip)
		slaveserver = StartSlaveServer()
		for {
			if !ishost {
				time.Sleep(time.Second * 5)
				fmt.Println("我是小弟", slaveserver)
			}
			//} else {
			//	time.Sleep(time.Second * 5)
			//}

		}

	} else {

		ishost = false
		RigsterETCD(valueip)
		slaveserver = StartSlaveServer()
		for {
			if !ishost {
				time.Sleep(time.Second * 5)
				fmt.Println("我是小弟", slaveserver)
			}
			//} else {
			//	time.Sleep(time.Second * 5)
			//}

		}
	}
	time.Sleep(time.Minute)
}

func StartHttpServer(slaveserverlist []string) *http.Server {
	var urllist []*url.URL
	for i := 0; i < len(slaveserverlist); i++ {
		urllist = append(urllist, &url.URL{
			Scheme: "http",
			Host:   slaveserverlist[i],
		})
	}
	proxy := NewServerlist(urllist)
	srv := &http.Server{
		Addr:    ":8081",
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

func StartSlaveServer() *HTTP {
	l, _ := net.Listen("tcp", ":8081")
	h := new(HTTP)
	h.listener = l
	go func() {
		http.Serve(h.listener, h)
	}()
	//time.Sleep(time.Second * 10)
	//h.listener.Close()
	return h
}
