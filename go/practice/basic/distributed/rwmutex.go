/*
Package distributed

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package distributed

import (
	"context"
	clientv3 "go.etcd.io/etcd/client/v3"
	"go.etcd.io/etcd/client/v3/concurrency"
	recipe "go.etcd.io/etcd/client/v3/experimental/recipes"
	"log"
	"math/rand"
	"sync"
	"time"
)

func main() {
	rand.New(rand.NewSource(time.Now().UnixNano()))

	endpoints := []string{"http://127.0.0.1:2379"}
	cli, err := clientv3.New(clientv3.Config{Endpoints: endpoints})
	if err != nil {
		log.Fatal(err)
	}
	defer cli.Close()

	var lockName = "my-lock123"
	var wg sync.WaitGroup
	wg.Add(20)

	for i := 0; i < 10; i++ {
		go startLockSession(i, cli, lockName, &wg)
	}

	for i := 0; i < 10; i++ {
		go startRLockSession(10+i, cli, lockName, &wg)
	}
	wg.Wait()
}

func startLockSession(id int, cli *clientv3.Client, lockName string, wg *sync.WaitGroup) {
	defer wg.Done()
	s1, err := concurrency.NewSession(cli)
	if err != nil {
		log.Fatal(err)
	}
	defer s1.Close()

	m1 := concurrency.NewMutex(s1, lockName)
	log.Println("acquiring lock for ID", id)
	if err := m1.Lock(context.TODO()); err != nil {
		log.Fatal(err)
	}
	log.Println("acquired lock for ID", id)

	time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
	if err := m1.Unlock(context.TODO()); err != nil {
		log.Fatal(err)
	}
	log.Println("released lock for ID", id)
}

func startRLockSession(id int, cli *clientv3.Client, lockName string, wg *sync.WaitGroup) {
	defer wg.Done()

	s1, err := concurrency.NewSession(cli)
	if err != nil {
		log.Fatal(err)
	}
	defer s1.Close()
	m1 := recipe.NewRWMutex(s1, lockName)

	log.Println("acquiring lock for ID", id)
	if err := m1.RLock(); err != nil {
		log.Fatal(err)
	}
	log.Println("acquired lock for ID", id)

	time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
	if err := m1.RUnlock(); err != nil {
		log.Fatal(err)
	}
	log.Println("released lock for ID", id)
}
