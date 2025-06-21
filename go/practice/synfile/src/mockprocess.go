package main

import (
	"fmt"
	"log"
	"time"
)

type MockProcess struct {
	isRunning bool
}

func (m *MockProcess) Run() {
	m.isRunning = true
	fmt.Println("Mock process running")
	for {
		fmt.Println(".")
		time.Sleep(1 * time.Second)
	}
}

func (m *MockProcess) Stop() {
	if !m.isRunning {
		log.Fatal("Cannot stop a process which is not running")
	}
	fmt.Println("Mock process stopped")
	for {
		fmt.Println(".")
		time.Sleep(1 * time.Second)
	}
}
