package myerror

import (
	"fmt"
	"net"
)

type Chanerr struct {
	Err    string
	Mychan chan string
}

func (e *Chanerr) Error() string {
	return fmt.Sprintf("chan exception closed err")
}

type NetWorkError struct {
	Err  string
	conn net.Conn
}

func (e *NetWorkError) Error() string {
	return fmt.Sprintf("net network error: %s", e.Err)
}
