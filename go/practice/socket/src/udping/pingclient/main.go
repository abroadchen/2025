package main

import "time"

const (
	DEFAULT_NETWORK               = "udp"
	SERVER_ADDR1                  = ":8000"
	SERVER_ADDR2                  = ":8001"
	PING                          = "ping"
	PONG                          = "pong"
	READ_TIMEOUT    time.Duration = time.Second * 1
	PING_NUM                      = 10
)

func main() {
	client := NewPingTool(READ_TIMEOUT, PING_NUM, DEFAULT_NETWORK)
	client.pingServerConcurrent(SERVER_ADDR1, SERVER_ADDR2)
}
