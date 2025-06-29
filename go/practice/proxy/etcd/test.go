package etcd

import (
	"fmt"
	"github.com/coreos/go-systemd/v22/dbus"
	clientv3 "go.etcd.io/etcd/client/v3"
	"io"
	"net/http"
	"net/url"
	"os"
	"strings"
	"time"
)

func ETCDRead(key string) string {
	var conf = clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	}
	eMutex := &EtcdMutex{Conf: conf, Tlt: 10, Key: key + "lock"}
AA:
	err := eMutex.Lock()
	if err != nil {
		fmt.Println("线程read抢锁失败,等待", err)
		time.Sleep(time.Second)
		goto AA
	} else {
		fmt.Println("线程read抢锁成功")
		returnstr := GetKey(key)
		defer eMutex.Unlock()
		fmt.Println("线程read结束")
		return returnstr
	}
}

func ETCDWrite(key, value string) bool {
	var conf = clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	}
	eMutex := &EtcdMutex{Conf: conf, Tlt: 10, Key: key + "lock"}
AA:
	err := eMutex.Lock()
	if err != nil {
		fmt.Println("线程Write抢锁失败,等待", err)
		time.Sleep(time.Second)
		goto AA
	} else {
		fmt.Println("线程Write抢锁成功")
		isok := Save(key, value)
		defer eMutex.Unlock()
		fmt.Println("线程Write结束")
		return isok
	}
}

func GetKey(key string) string {
	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	})
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("连接成功")
	defer cli.Close()
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*3)
	resp, err := cli.Get(ctx, key)
	cancel()
	if err != nil {
		fmt.Println("get", err)
		return ""
	}
	//mylist := []string{}
	mystr := ""
	for _, ev := range resp.Kvs {
		fmt.Println(string(ev.Key), string(ev.Value))
		if string(ev.Key) == key {
			mystr = string(ev.Value)
		}
	}
	//mylist = strings.Split(mystr, "#$#")
	return mystr
}

func Save(key, value string) bool {
	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	})
	if err != nil {
		fmt.Println(err)
		return false
	}
	fmt.Println("连接成功")
	defer cli.Close()
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*3)
	_, err = cli.Put(ctx, key, value)
	cancel()
	if err != nil {
		fmt.Println("put", err)
		return false
	}
	return true
}

func checkHost(url string) bool {
	if len(url) < len("1.1.1.1") {
		return false
	}
	//url := "http://127.0.0.1:8080/"
	//if "" != os.Getenv("URL") {
	//	url = os.Getenv("URL")
	//}
	log.Printf("Target %s", url)
	resp, err := http.Get(url)
	if nil != err {
		//log.Fatal(err.Error())
		return false
	}
	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)
	if nil != err {
		//log.Fatal(err.Error())
		return false
	}
	println("正常", string(body))
	return true
}

func SlaveServer(url string) {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		body, _ := json.Marshal(map[string]string{
			"addr": r.RemoteAddr,
		})
		fmt.Println(string(body))
		w.Write(body)
	})
	http.ListenAndServe(url, nil)
}

func MasterServer(urls []string) {
	var myURLs []*url.URL
	for _, url := range urls {
		myURLs = append(myURLs, &url.URL{
			Scheme: "http",
			Host:   url
		})
	}
	proxy := NewMultipleHostsReverseProxy(myURLs)
	log.Fatal(http.ListenAndServe(":8090", proxy))
}

func Monitor()  {
	for {
		time.Sleep(time.Minute * 120)
	}
}

func main() {
	ishost := true
	if ishost {

	} else {

	}
	Monitor()
}