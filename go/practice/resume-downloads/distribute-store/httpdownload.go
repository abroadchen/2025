/*
Package 分布式存储
@author: chen
@since: 2025/7/14
@desc:
*/
package distribute_store

import (
	"io"
	"net/http"
	"os"
)

func main() {
	url := ""
	res, err := http.Get(url)
	if err != nil {
		panic(err)
	}
	file, err := os.Create("1.html")
	if err != nil {
		panic(err)
	}

	io.Copy(file, res.Body)
}
