package main

import (
	"log"
	"net"
	"sync"
	"time"
)

type PinngClient struct {
	timeout time.Duration
	pingnum int
	network string
	wg      *sync.WaitGroup
}

func NewPingTool(timeout time.Duration, pingnum int, network string) *PinngClient {
	return &PinngClient{
		timeout: timeout,
		pingnum: pingnum,
		network: network,
		wg:      &sync.WaitGroup{},
	}
}

func (client *PinngClient) PingServer(servers ...string) [][]int64 {
	n := len(servers)
	res := make([][]int64, n)
	for i := 0; i < n; i++ {
		res[i] = make([]int64, client.pingnum)
	}
	for i := 0; i < n; i++ {
		res[i] = client.pingServer(servers[i])
	}
	return res
}

func (client *PinngClient) pingServerConcurrent(servers ...string) [][]int64 {
	n := len(servers)
	res := make([][]int64, n)
	for i := 0; i < n; i++ {
		res[i] = make([]int64, client.pingnum)
	}
	client.wg.Add(n)
	for i := 0; i < n; i++ {
		go func(i int) {
			res[i] = client.pingServer(servers[i])
			client.wg.Done()
		}(i)
	}
	client.wg.Wait()
	return res
}

func (client *PinngClient) pingServer(server string) []int64 {
	rtts := make([]int64, client.pingnum)
	conn, err := net.DialTimeout(client.network, server, time.Second)
	if err != nil {
		log.Fatalf("try to #{server} #{client.network}")
	}
	for i := 0; i < client.pingnum; i++ {
		t1 := time.Now()
		_, err := conn.Write([]byte(PING))
		if err != nil {
			log.Fatalf("#{i} ping #{server} err #{err}\n")
			continue
		}
		_ = conn.SetReadDeadline(t1.Add(client.timeout))
		buff := make([]byte, 1024)
		n, err := conn.Read(buff)
		if err != nil {
			log.Fatalf("#{i} ping #{server} err #{err}\n")
			continue
		}
		t2 := time.Now()
		rtts[i] = t2.Sub(t1).Nanoseconds()
		log.Printf("#{i} ping #{server} receied #{string(buf[:n])}, time:#{t2.Sub(t1).Round(time.Millisecond).String()}\n")
	}
	return rtts
}
