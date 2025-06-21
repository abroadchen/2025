package memmerge

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

type QQ struct {
	QQtimes  int
	password string
}

func GetLineNumbers(oldpath string) int {
	fmt.Println("开始统计行数", oldpath)
	fi, err := os.Open(oldpath)
	if err != nil {
		fmt.Println(err)
	}
	defer fi.Close()
	br := bufio.NewReader(fi)
	i := 0
	for {
		_, _, err := br.ReadLine()
		if err == io.EOF {
			break
		}
		if i%10000 == 0 {
			fmt.Println(i)
		}
		i++
	}
	fmt.Println("结束统计", oldpath, i)
	return i
}
