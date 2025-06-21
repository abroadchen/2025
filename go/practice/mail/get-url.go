package mail

import (
	"bytes"
	"golang.org/x/net/html"
	"io"
	"net/http"
	"strings"
)

func GetURL(url string) []string {
	resp, err := http.Get(url)
	if err != nil {
		return []string{}
	}
	defer resp.Body.Close()

	b, err := io.ReadAll(resp.Body)
	if err != nil {
		return []string{}
	}

	doc, err := html.Parse(bytes.NewReader(b))
	if err != nil {
		return []string{}
	}

	tmplist := []string{}
	for _, link := range visit(nil, doc) {
		if !strings.Contains(link, "javascript") &&
			!strings.Contains(link, "#fabu_anchor") &&
			!strings.Contains(link, "#") {

			link = strings.Replace(link, "“", "\"", -1)
			if len(link) >= 5 && link[:4] != "http" {
				link = "http://bbs.tianya.cn" + link
			}
			tmplist = append(tmplist, link)
		}
	}

	return tmplist
}
