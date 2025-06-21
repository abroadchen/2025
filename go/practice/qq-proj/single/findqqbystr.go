package single

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
)

func FindQQbyString(word string, savepath string) []string {
	fi, err := os.Open(Qqpath)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	defer fi.Close()

	res := []string{}
	svfile, err := os.Create(savepath)
	if err != nil {
		fmt.Println(err)
	}
	sv := bufio.NewWriter(svfile)
	br := bufio.NewReader(fi)
	for {
		line, _, err := br.ReadLine()
		if err == io.EOF {
			break
		}
		lineStr := string(line)
		if strings.Contains(lineStr, word) {
			res = append(res, lineStr)
			fmt.Fprintln(sv, lineStr)
		}
	}
	sv.Flush()
	svfile.Close()
	return res
}
