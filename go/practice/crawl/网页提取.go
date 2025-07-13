package crawl

import (
	"fmt"
	"io"
	"net/http"
	"regexp"
	"sync"
	"time"
)

func main1() {
	url := ""
	urllist := GetURL(url)
	urllist = append(urllist, url)
	emaillist := []string{}
	for _, myurl := range urllist {
		tmplist := GetEmail(myurl)
		for _, email := range tmplist {
			emaillist = append(emaillist, email)
		}
	}
}

func main() {
	url := ""
	urllist := GetURL(url)
	urllist = append(urllist, url)
	var wg sync.WaitGroup
	wg.Add(len(urllist))
	for i := 0; i < len(urllist); i++ {
		//wg.Add(1)
		go func(i int, myurl string) {
			timeout := time.Second * 5
			var timer *time.Timer
			go GetEmail(myurl, i)
			for {
				if timer == nil {
					timer = time.NewTimer(timeout)
				} else {
					timer.Reset(timeout)
				}

				select {

				case <-timer.C:
					fmt.Println("timeout")
					wg.Done()
					return
				}
			}
		}(i, urllist[i])

	}
	wg.Wait()
	fmt.Println("finish")
}

func GetEmail(url string, id int) []string {
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	b, err := io.ReadAll(resp.Body)
	resp.Body.Close()
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	fmt.Println(string(b))
	reg := ``
	rgx := regexp.MustCompile(reg)
	tmplist := rgx.FindAllString(string(b), -1)
	for _, email := range tmplist {
		fmt.Println(email, " ", id)
	}
	//wg.Done()
	return tmplist
}
