/*
Package rpc

	@author: June
	@since: 2025/7/18
	@desc:
*/
package rpc

import (
	"fmt"
	"net/rpc/jsonrpc"
)

func main() {
	conn, err := jsonrpc.Dial("tcp", "127.0.0.1:1234")
	if err != nil {
		fmt.Println(err)
	}

	req := ArithRequest{A: 10, B: 20}
	var res ArithResponse

	err = conn.Call("ArithService.Divide", req, &res)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(res.Pro)
}
