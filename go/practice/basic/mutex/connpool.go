/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"fmt"
	"github.com/fatih/pool"
	"net"
)

func main() {
	factory := func() (net.Conn, error) {
		return net.Dial("tcp", "127.0.0.1:8080")
	}

	p, err := pool.NewChannelPool(5, 30, factory)
	if err != nil {
		panic(err)
	}
	conn, err := p.Get()
	conn.Close()

	fmt.Println(conn, err)
}
