/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

import (
	"context"
	"fmt"
	clientv3 "go.etcd.io/etcd/client/v3"
	"go.etcd.io/etcd/client/v3/concurrency"
	"math/rand"
	"strconv"
	"sync"
)

func main() {
	endpoints := []string{"http://127.0.0.1:2379"}
	cli, err := clientv3.New(clientv3.Config{Endpoints: endpoints})
	if err != nil {
		fmt.Println(err)
	}
	defer cli.Close()

	totalAccounts := 5
	for i := 0; i < totalAccounts; i++ {
		k := fmt.Sprintf("accts-%d", i)
		if _, err := cli.Put(context.Background(), k, strconv.Itoa(i)); err != nil {
			fmt.Println(err)
		}
	}
	exchange := func(stm concurrency.STM) error {
		from, to := rand.Intn(totalAccounts), rand.Intn(totalAccounts)
		if from == to {
			return nil
		}
		fromK, toK := fmt.Sprintf("accts-%d", from), fmt.Sprintf("accts-%d", to)
		fromV, toV := stm.Get(fromK), stm.Get(toK)
		fromInt, toInt := 0, 0
		fmt.Sscanf(fromV, "%d", &fromInt)
		fmt.Sscanf(toV, "%d", &toInt)
		xfer := fromInt / 2
		fromInt, toInt = fromInt-xfer, toInt+xfer

		stm.Put(fromK, strconv.Itoa(fromInt))
		stm.Put(toK, strconv.Itoa(toInt))
		return nil
	}

	var wg sync.WaitGroup
	wg.Add(10)
	for i := 0; i < 10; i++ {
		go func() {
			defer wg.Done()
			if _, serr := concurrency.NewSTM(cli, exchange); serr != nil {
				fmt.Println(serr)
			}
		}()
	}
	wg.Wait()
}
