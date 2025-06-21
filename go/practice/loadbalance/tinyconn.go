package main

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
	conns[0].servername = "a"
	conns[1].servername = "a"
	conns[2].servername = "a"
	conns[0].livetasks = 3
	conns[0].livetasks = 3
	conns[0].livetasks = 3

	for i := 0; i < 100; i++ {
		conns[GetMin(conns)].livetasks += 1
	}
}
