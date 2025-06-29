package single

import (
	"fmt"
	"github.com/wangbin/jiebago"
	"os"
)

var seg jiebago.Segmenter

func init() {
	seg.LoadDictionary("dict.txt")
}

func print(ch <-chan string) {
	for word := range ch {
		fmt.Println(" %s /", word)
	}
	fmt.Println()
}

func main() {
	fmt.Println("全模式")
	print(seg.CutAll(""))

	fmt.Println("<精确模式>")
	print(seg.Cut("", false))

	fmt.Println("<新词识别>")
	print(seg.Cut("", true))

	fmt.Println("<搜索引擎模式>")
	print(seg.CutForSearch("<UNK>", true))
}
