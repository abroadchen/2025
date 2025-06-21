package GetMail

import (
	"io/ioutil"
	"net/http"
	"regexp"
)

func GetMail(url string) []string {
	resp, err := http.Get(url)
	if err != nil {
		return []string{}
	}
	b, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return []string{}
	}
	reg := `[\w-]+(\.[\w-]+)*@[\w-]+(\.[\w-]+`
	rgx := regexp.MustCompile(reg)
	tmplist := rgx.FindAllString(string(b), -1)
	return tmplist
}
