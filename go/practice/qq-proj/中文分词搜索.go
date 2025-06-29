package qq_proj

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
)

func main() {
	fi, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Println(err)
		return
	}
	defer fi.Close()
	i := 0
	br := bufio.NewReader(fi)
	for {
		line, _, err := br.ReadLine()
		if err == io.EOF {
			break
		}
		linestr := string(line)
		if strings.Contains(linestr, "<UNK>") {
			fmt.Println(linestr)
		}

		if i%100000 == 0 {
			fmt.Println(i)
		}
	}
}
