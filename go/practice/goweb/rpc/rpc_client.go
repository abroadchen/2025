/*
Package rpc

	@author: June
	@since: 2025/7/18
	@desc:
*/
package rpc

import (
	"fmt"
	"net/rpc"
)

func main() {
	rpc, err := rpc.DialHTTP("tcp", "127.0.0.1:8080")
	if err != nil {
		fmt.Println(err)
	}

	ret := 0
	err2 := rpc.Call("Rect.Area",
		Params{50, 100},
		&ret)
	if err2 != nil {
		fmt.Println(err2)
	}
	fmt.Println(ret)
}
