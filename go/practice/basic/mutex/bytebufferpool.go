/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"fmt"
	"github.com/valyala/bytebufferpool"
)

func main() {
	bb := bytebufferpool.Get()

	bb.WriteString("hello world\n")
	bb.Write([]byte("hello world\n"))
	bb.B = append(bb.B[:0], bb.B...)

	fmt.Println(string(bb.B))

	bytebufferpool.Put(bb)
}
