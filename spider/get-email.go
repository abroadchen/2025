package spider

import (
	"io/ioutil"
	"net/http"
	"regexp"
)

func GetEmail(url string, emailmap map[string]int) []string {
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
