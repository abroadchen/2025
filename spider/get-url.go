package spider

import (
	"fmt"
	"io"
	"net/http"
	"strings"
	"sync/atomic"
)

var threadnum int32

func GetURL(url string, p *int32) []string {
	atomic.AddInt32(p, 1)
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	b, err := io.ReadAll(resp.Body)
	if err != nil {
		return []string{}
	}
	err = resp.Body.Close()
	if err != nil {
		return []string{}
	}
	fmt.Println(string(b))
	atomic.AddInt32(p, -1)
	return strings.Split(string(b), "\n")
}

func main() {
	url := "https://studygolang.com/articles/16945?fr=sidebar"
	fmt.Println(GetURL(url))
}
