package GetURL

import (
	"golang.org/x/net/html"
	"io/ioutil"
	"my-distributed-project/webPageGet/GetURL/RandomStr"
	"net/http"
	"os"
	"strings"
)

func GetURL(url string) []string {
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
	os.Remove(filename)
	return tmplist
}

func GetURL2(url string, urlmap map[string]int) []string {
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
	if n == nil {
		return []string{}
	}
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
