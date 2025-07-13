package crawl

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"regexp"
)

func main1() {
	reg := ``
	rgx := regexp.MustCompile(reg)
	fmt.Println(rgx.Match([]byte("")))
	fmt.Println(rgx.FindAllString("", -1))
}

func main() {
	fi, err := os.Open("mail.txt")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer fi.Close()

	br := bufio.NewReader(fi)
	reg := ``
	rgx := regexp.MustCompile(reg)
	listall := []string{}
	for {
		line, _, err := br.ReadLine()
		if err == io.EOF {
			break
		}
		linestr := string(line)
		tmplist := rgx.FindAllString(linestr, -1)
		if len(tmplist) != 0 {
			for _, email := range tmplist {
				listall = append(listall, email)
			}
		}
	}
	fmt.Println(listall)
}
