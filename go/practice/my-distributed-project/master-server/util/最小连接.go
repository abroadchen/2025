package util

import "github.com/gogo/protobuf/protoc-gen-gogo/testdata/imports/fmt"

type CONN struct {
	servername string
	livetasks  int
}

func GetMin(conns []CONN) int {
	if conns[0].livetasks > conns[1].livetasks {
		if conns[1].livetasks > conns[2].livetasks {
			return 2
		} else {
			return 1
		}
	} else {
		if conns[0].livetasks > conns[2].livetasks {
			return 2
		} else {
			return 0
		}
	}
}

func main() {
	conns := make([]CONN, 3, 3)
	conns[0].servername = "A"
	conns[1].servername = "B"
	conns[2].servername = "C"
	conns[0].livetasks = 5
	conns[1].livetasks = 6
	conns[2].livetasks = 7

	for i := 0; i < 100; i++ {
		conns[GetMin(conns)].livetasks += 1
		fmt.Println(conns[0].servername, conns[1].servername, conns[2].servername)
		fmt.Println(conns[0].livetasks, conns[1].livetasks, conns[2].livetasks)
	}
}
