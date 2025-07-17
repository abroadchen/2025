/*
Package crawl

	@author: chen
	@since: 2025/7/15
	@desc: 高并发 双队列
*/
package crawl

import (
	"container/list"
	"fmt"
	"io"
	"net/http"
	"regexp"
)

func worker(id int, jobs <-chan string, results chan<- string) {
	url := <-jobs
	//for url := range jobs {
	tmplist := getMail(url)
	for _, email := range tmplist {
		results <- email
		fmt.Println("<-", email, id)
	}

	//}
}

func main() {
	jobs := make(chan string, 100)
	results := make(chan string, 100)

	go func() {
		url := "https://mail.google.com/mail/"

		myqueue := list.New()
		myqueue.PushBack(url)
		level := 0
		for myqueue.Len() != 0 {
			myurl := myqueue.Front()
			fmt.Println(myurl.Value.(string))

			go worker(level, jobs, results)
			jobs <- myurl.Value.(string)

			myqueue.Remove(myurl)
			urllist := GetURL2(myurl.Value.(string))
			for _, geturl := range urllist {
				myqueue.PushBack(geturl)
			}
			level++
			if level > 3 {
				break
			}
		}
	}()

	for {
		fmt.Println("get", <-results)
	}

}

func getMail(url string) []string {
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
