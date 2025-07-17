/*
Package distributed

	@author: chen
	@since: 2025/7/16
	@desc:
*/
package distributed

import (
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	recipe "go.etcd.io/etcd/client/v3/experimental/recipes"
	"log"
	"math/rand"
	"sync"
	"time"
)

func main() {
	rand.New(rand.NewSource(time.Now().UnixNano()))

	endpoints := []string{"http://localhost:2379"}
	cli, err := clientv3.New(clientv3.Config{Endpoints: endpoints})
	if err != nil {
		log.Fatal(err)
	}
	defer cli.Close()

	var queueName = "my-queue"
	var wg sync.WaitGroup
	wg.Add(20)

	for i := 0; i < 10; i++ {
		go write(i, cli, queueName, &wg)
	}
	for i := 0; i < 10; i++ {
		go read(10+i, cli, queueName, &wg)
	}
	wg.Wait()
}

func write(id int, cli *clientv3.Client, queueName string, wg *sync.WaitGroup) {
	defer wg.Done()
	q := recipe.NewQueue(cli, queueName)
	for i := 0; i < 10; i++ {
		q.Enqueue(fmt.Sprintf("g-id-key-%d", id))
	}
}

func read(id int, cli *clientv3.Client, queueName string, wg *sync.WaitGroup) {
	defer wg.Done()

	q := recipe.NewQueue(cli, queueName)
	for i := 0; i < 10; i++ {
		v, err := q.Dequeue()
		if err != nil {
			log.Fatal(err)
		}
		fmt.Printf("g-id-key-%d: value: %s\n", id, v)
	}
}
