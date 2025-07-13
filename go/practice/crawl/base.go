package crawl

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"regexp"
)

var (
	reEmail  = ``
	reLinke  = `href=`
	rePhone  = ``
	reIdcard = ``
	reImg    = ``
)

func GetImg(url string) {
	pageStr := GetPageStr(url)
	re := regexp.MustCompile(reImg)
	results := re.FindAllStringSubmatch(pageStr, -1)
	for _, result := range results {
		fmt.Println(result[0])
	}
}

func GetPhone(url string) {
	pageStr := GetPageStr(url)
	re := regexp.MustCompile(rePhone)
	results := re.FindAllStringSubmatch(pageStr, -1)
	for _, result := range results {
		fmt.Println(result)
	}
}

func GetLink(url string) {
	pageStr := GetPageStr(url)
	re := regexp.MustCompile(reLinke)
	results := re.FindAllStringSubmatch(pageStr, -1)
	for _, result := range results {
		fmt.Println(result[1])
	}
}

func GetPageStr(url string) (pageStr string) {
	resp, err := http.Get(url)
	HandleError(err, "http.Get url")
	defer resp.Body.Close()
	pageBytes, err := ioutil.ReadAll(resp.Body)
	HandleError(err, "ioutil.ReadAll resp.Body")
	pageStr = string(pageBytes)
	return
}

func HandleError(err error, msg string) {
	if err != nil {
		fmt.Println(msg, err)
	}
}

func getImgs(url string) (urls []string) {
	pageStr := GetPageStr(url)
	re := regexp.MustCompile(reImg)
	results := re.FindAllStringSubmatch(pageStr, -1)
	fmt.Printf("results: %d\n", len(results))
	for _, result := range results {
		url := result[0]
		urls = append(urls, url)
	}
}
