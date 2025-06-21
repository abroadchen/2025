package myMap

import (
	"bufio"
	"container/list"
	"fmt"
	"golang.org/x/net/html"
	"io/ioutil"
	"my-distributed-project/webPageGet/GetURL/RandomStr"
	"net/http"
	"os"
	"regexp"
	"strings"
	"sync"
)

type MyMap struct {
	datamap map[string]int
	mutex   *sync.RWMutex
}

func NewMyMap() *MyMap {
	mymap := new(MyMap)
	mymap.datamap = make(map[string]int)
	mymap.mutex = new(sync.RWMutex)
	return mymap
}

func (mymap *MyMap) Isin(key string) bool {
	var isok bool
	mymap.mutex.RLock()
	_, ok := mymap.datamap[key]
	if ok {
		isok = true
	} else {
		isok = false
	}
	return isok
}

func (mymap *MyMap) Get(key string) int {
	mymap.mutex.RLock()
	data, ok := mymap.datamap[key]
	mymap.mutex.RUnlock()
	if ok {
		return data
	}
	panic("err, not exist")
}

func (mymap *MyMap) Getall() ([]string, []int) {
	mymap.mutex.RLock()
	keylist := []string{}
	valuelist := []int{}
	for k, v := range mymap.datamap {
		keylist = append(keylist, k)
		valuelist = append(valuelist, v)
	}
	mymap.mutex.RUnlock()
	return keylist, valuelist
}

func (mymap *MyMap) Set(key string, value int) {
	mymap.mutex.Lock()
	mymap.datamap[key] = value
	mymap.mutex.Unlock()
}

type SafeFile struct {
	mutex    *sync.Mutex
	savefile *os.File
}

func GetMail1(url string, mymap *MyMap, sf *SafeFile) []string {
	resp, err := http.Get(url)
	if err != nil {
		return []string{}
	}
	b, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return []string{}
	}
	reg := ``
	rgx := regexp.MustCompile(reg)
	tmplist := rgx.FindAllString(string(b), -1)
	lastlist := []string{}
	for i := 0; i < len(tmplist); i++ {
		isok := mymap.Isin(tmplist[i])
		if isok {
			num := mymap.Get(tmplist[i])
			mymap.Set(tmplist[i], num)
		} else {
			mymap.Set(tmplist[i], 1)
			lastlist = append(lastlist, tmplist[i])
		}
	}

	sf.mutex.Lock()
	save := bufio.NewWriter(sf.savefile)
	for i := 0; i < len(lastlist); i++ {
		fmt.Println(lastlist[i])
		fmt.Fprintln(save, lastlist[i])
	}
	save.Flush()
	sf.mutex.Unlock()
	return lastlist
}

func GetURL(url string, urlmap map[string]int) []string {
	resp, err := http.Get(url)
	if err != nil {
		return []string{}
	}
	b, err := ioutil.ReadAll(resp.Body)
	resp.Body.Close()
	if err != nil {
		return []string{}
	}
	filename := RandomStr.GetRandomSalt() + "1.txt"
	file, err := os.Create(filename)
	file.Write(b)
	file.Close()
	newfile, _ := os.Open(filename)
	doc, err := html.Parse(newfile)
	tmplist := []string{}
	lastlist := []string{}
	for _, link := range visit(nil, doc) {
		if !strings.Contains(link, "javascript") && !strings.Contains(link, "#fabu_anchor") && !strings.Contains(link, "#") {
			link = strings.Replace(link, "“", "\"", -1)
			if len(link) >= 5 && link[:4] != "http" {
				link = "http://bbs.tianya.cn" + link
			}
			//fmt.Println(link)
			tmplist = append(tmplist, link)
			for i := 0; i < len(tmplist); i++ {
				_, ok := urlmap[tmplist[i]]
				if ok {
					urlmap[tmplist[i]] = urlmap[tmplist[i]] + 1
				} else {
					urlmap[tmplist[i]] = 1
					lastlist = append(lastlist, tmplist[i])
				}
			}
		}
	}
	os.Remove(filename)
	newfile.Close()
	return lastlist
}

func visit(links []string, n *html.Node) []string {
	if n.Type == html.ElementNode && n.Data == "a" {
		for _, a := range n.Attr {
			if a.Key == "href" {
				links = append(links, a.Val)
			}
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		links = visit(links, c)
	}
	return links
}

func main() {
	mymap := NewMyMap()
	var sf = new(SafeFile)
	sf.mutex = new(sync.Mutex)
	sf.savefile, _ = os.Create("lastemailsafe.txt")
	defer sf.savefile.Close()
	urlmap := make(map[string]int)
	url := ""
	myqueue := list.New()
	myqueue.PushBack(url)
	for myqueue.Len() != 0 {
		myurl := myqueue.Front()
		go GetMail1(myurl.Value.(string), mymap, sf)
		myqueue.Remove(myurl)
		urllist := GetURL(myurl.Value.(string), urlmap)
		for _, url := range urllist {
			myqueue.PushBack(url)
		}
	}
}
