/*
Package crawl

	@author: chen
	@since: 2025/7/15
	@desc:
*/
package crawl

import (
	"container/list"
	"fmt"
	"github.com/dokidokikoi/go-cmap"
	"golang.org/x/net/html"
	"io"
	"net/http"
	"os"
	"regexp"
	"strings"
	"sync/atomic"
	"time"
)

var threadnum int32

func main() {

	concurrency := 10000
	cm, _ := cmap.NewConcurrentMap(concurrency, nil)

	urlmap := make(map[string]int)
	url := "https://mail.google.com/mail/"

	go func() {
		for {
			fmt.Println("现在有", atomic.LoadInt32(&threadnum), "个线程还在")
			time.Sleep(5 * time.Second)
		}
	}()

	myqueue := list.New()
	myqueue.PushBack(url)
	level := 0
	for myqueue.Len() != 0 {
		myurl := myqueue.Front()
		fmt.Println(myurl.Value.(string))

		go GetMail(myurl.Value.(string), &threadnum, cm)

		myqueue.Remove(myurl)
		urllist := GetURL(myurl.Value.(string), urlmap)
		for _, geturl := range urllist {
			_, ok := urlmap[geturl]
			if ok {
				urlmap[geturl]++
			} else {
				urlmap[geturl] = 1
				myqueue.PushBack(geturl)
			}
		}
		level++
		if level > 3 {
			break
		}
	}
	//for k, v := range urlmap {
	//	fmt.Println(k, v)
	//}
}

func GetURL(url string, urlmap map[string]int) []string {
	resp, err := http.Get(url)
	if err != nil {
		return []string{}
	}
	b, err := io.ReadAll(resp.Body)
	resp.Body.Close()
	if err != nil {
		return []string{}
	}
	file, err := os.Create("1.txt")
	file.Write(b)
	file.Close()
	newfile, _ := os.Open("1.txt")
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

func GetMail(url string, p *int32, cm cmap.ConcurrentMap) []string {
	atomic.AddInt32(p, 1)
	resp, err := http.Get(url)
	if err != nil {
		return []string{}
	}
	b, err := io.ReadAll(resp.Body)
	if err != nil {
		return []string{}
	} //qq ^[1-9]\\d{4,10}$
	reg := `^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(.[a-zA-Z0-9_-]+)+$`
	rgx := regexp.MustCompile(reg)
	tmplist := rgx.FindAllString(string(b), -1)
	for _, email := range tmplist {

		actualElement := cm.Get(email)
		if actualElement == nil {
			cm.Put(email, 1)
			fmt.Println(email)
		} else {
			cm.Put(email, actualElement.(int)+1)
		}
	}
	atomic.AddInt32(p, -1)
	return tmplist
}
