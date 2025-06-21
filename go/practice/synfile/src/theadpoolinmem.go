package main

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"strings"
	"time"
)

type ThreadPool struct {
	Queue          chan func() error
	Number         int
	Total          int
	result         chan error
	finishCallback func()
}

func (t *ThreadPool) Init(number int, total int) {
	t.Queue = make(chan func() error, total)
	t.Number = number
	t.Total = total
	t.result = make(chan error, total)
}

func (t *ThreadPool) Start() {
	for i := 0; i < t.Number; i++ {
		go func() {
			for {
				task, ok := <-t.Queue
				if !ok {
					break
				}
				err := task()
				t.result <- err
			}
		}()
	}
	for j := 0; j < t.Total; j++ {
		res, ok := <-t.result
		if !ok {
			break
		}
		if res != nil {
			fmt.Println(res)
		}
	}
	if t.finishCallback != nil {
		t.finishCallback()
	}
}

func (t *ThreadPool) Finish() {
	close(t.Queue)
	close(t.result)
}

func (t *ThreadPool) AddTask(task func() error) {
	t.Queue <- task
}

func (t *ThreadPool) SetFinishCallback(callback func()) {
	t.finishCallback = callback
}

func Download(url string) error {
	fmt.Println("Downloading", url)
	sp := strings.Split(url, "/")
	filename := sp[len(sp)-1]
	path := ""
	file, err := os.Create(path + filename)
	if err != nil {
		return err
	}
	res, err := http.Get(url)
	if err != nil {
		return err
	}
	length, err := io.Copy(file, res.Body)
	if err != nil {
		return err
	}
	fmt.Println("finished", url, length)
	return nil
}

func main() {
	urls := []string{}
	pool := new(ThreadPool)
	pool.Init(2, len(urls))
	for i := range urls {
		url := urls[i]
		pool.AddTask(func() error {
			return Download(url)
		})
	}
	isok := false
	pool.SetFinishCallback(func() {
		func(pisok *bool) {
			*pisok = true
		}(&isok)
	})
	pool.Start()
	for !isok {
		time.Sleep(time.Second)
	}
	pool.Finish()
	fmt.Println("mission finished")
}
