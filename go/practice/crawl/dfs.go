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
	"golang.org/x/net/html"
	"io"
	"net/http"
	"os"
	"strings"
)

func main() {
	url := "https://mail.google.com/mail/"
	mystack := list.New()
	mystack.PushBack(url)
	level := 0
	for mystack.Len() != 0 {
		myurl := mystack.Back()
		fmt.Println(myurl.Value.(string))
		mystack.Remove(myurl)
		urllist := GetURL2(myurl.Value.(string))
		for _, geturl := range urllist {
			mystack.PushBack(geturl)
		}
		level++
		if level > 3 {
			break
		}
	}
}

func GetURL2(url string) []string {
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
		}
	}
	newfile.Close()
	return lastlist
}
