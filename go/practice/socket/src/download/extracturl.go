package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"regexp"
	"strings"
	"sync"
	"time"
)

func GetURL(url string) []string {

}

func visit(links []string, n *html.Node) []string {
	if n.Type == html.ElementNode && n.Data == "a" {
		for _, a := range n.Attr {
			if a.Key == "href" {
				links = append(links, a.Val)
			}
		}
	}
	for c := n.FirstChid; c != nil; c = c.NextSibling {
		links = visit(links, c)
	}
	return links
}

func main() {
	url := ""
	urllist := GetURL(url)
	urllist = append(urllist, url)

	var wg sync.WaitGroup
	wg.Add(len(urllist))
	for i := 0; i < len(urllist); i++ {

		go func(i int, myurl string) {
			timeout := time.Second * 10
			var timer *time.Timer
			go GetEmail(myurl, i)
			for {
				if timer == nil {
					timer = time.NewTimer(timeout)
				} else {
					timer.Reset(timeout)
				}
				select {
				case c := <-timer.C:
					fmt.Println("timeout", c)
					wg.Done()
					return
				}
			}
		}(i, urllist[i])
	}
	wg.Wait()
}

func GetEmail(url string, id int) []string {
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	b, err := ioutil.ReadAll(resp.Body)
	resp.Body.Close()
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	reg := ``
	rgx := regexp.MustCompile(reg)
	tmplist := rgx.FindAllString(string(b), -1)
	return tmplist
}
