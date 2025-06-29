package mail

import (
	"container/list"
	"fmt"
	"golang.org/x/net/html"
	"io"
	"io/ioutil"
	"net/http"
	"os"
	"regexp"
	"strconv"
	"strings"
	"sync"
	"time"
)

func GetMail1(url string) []string {
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
	return tmplist
}

func GetMail2(url string, wg *sync.WaitGroup) []string {
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
	wg.Done()
	return tmplist
}

func mainwait() {
	var wg sync.WaitGroup
	for i := 1; i <= 8; i++ {
		url := "https://mail.google.com/" + strconv.Itoa(i) + ".shtml"
		wg.Add(1)
		go GetMail2(url, &wg)
	}
	wg.Wait()
	fmt.Println("等待所有线程都干完")
	time.Sleep(1 * time.Second)
}

func GetMail(url string, emailmap map[string]int) []string {
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
		_, ok := emailmap[tmplist[i]]
		if ok {
			emailmap[tmplist[i]] = emailmap[tmplist[i]] + 1
		} else {
			emailmap[tmplist[i]] = 1
			lastlist = append(lastlist, tmplist[i])
		}
	}
	return lastlist
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

// GetURL 去重/**
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

func main2() {
	urlmap := make(map[string]int)
	urlEmail := make(map[string]int)
	url := ""
	//1
	mystack := list.New()
	mystack.PushBack(url)
	for mystack.Len() != 0 {
		myurl := mystack.Back()
		fmt.Println(myurl.Value.(string), GetMail(myurl.Value.(string), urlEmail))
		mystack.Remove(myurl)
		urllist := GetURL(myurl.Value.(string), urlmap)
		for _, url := range urllist {
			mystack.PushBack(url)
		}
	}
	//2
	myqueue := list.New()
	myqueue.PushBack(url)
	for myqueue.Len() != 0 {
		myurl := myqueue.Front()
		fmt.Println(myurl.Value.(string), GetMail(myurl.Value.(string), urlEmail))
		myqueue.Remove(myurl)
		urllist := GetURL(myurl.Value.(string), urlmap)
		for _, url := range urllist {
			myqueue.PushBack(url)
		}
	}

	urllist := GetURL(url, urlmap)
	for i := 0; i < len(urllist); i++ {
		fmt.Println(i, GetMail(urllist[i], urlEmail))
		urllist2 := GetURL(urllist[i], urlmap)
		for j := 0; j < len(urllist2); j++ {
			fmt.Println(i, j, GetMail(urllist2[i], urlEmail))
		}
	}
}

func main() {
	urlchan := make(chan string, 1000)
	emailchan := make(chan string, 1000)
	go func() {
		url := ""
		myqueue := list.New()
		myqueue.PushBack(url)
		for myqueue.Len() != 0 {
			myurl := myqueue.Front()
			urlchan <- myurl.Value.(string)
			urllist := GetURL2(myurl.Value.(string))
			for _, url := range urllist {
				myqueue.PushBack(url)
			}
		}
	}()

	for i := 0; i < 5; i++ {
		go func(id int) {
			for {
				if elem, ok := <-urlchan; ok {
					fmt.Println(id, "receive url", elem)
					emaillist := GetMail1(elem)
					for _, email := range emaillist {
						//fmt.Println(id, email)
						emailchan <- email
					}
				} else {
					fmt.Println("chan has closed")
					break
				}
			}
		}(i)
	}
	//time.Sleep(time.Second * 100)
	for {
		select {
		case e, ok := <-emailchan:
			if ok {
				fmt.Println("received", e)
			}
		}
	}
}
