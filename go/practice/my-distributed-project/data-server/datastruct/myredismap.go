package datastruct

import (
	"context"
	"github.com/redis/go-redis/v9"
)

type MyRedisMap struct {
	client   *redis.Client
	id       int
	password string
	addr     string
}

func NewMyRedisMap(id int, password string, addr string) *MyRedisMap {
	mymap := new(MyRedisMap)
	mymap.client = redis.NewClient(&redis.Options{
		Addr:     addr,
		Password: password,
		DB:       id,
	})
	_, err := mymap.client.Ping(context.Background()).Result()
	if err != nil {
		return nil
	}
	return mymap
}

func (mymap *MyRedisMap) Isin(key string) bool {
	if mymap.client != nil {
		_, err := mymap.client.Get(context.Background(), key).Result()
		if err == redis.Nil {
			return false
		} else if err != nil {
			panic(err)
		} else {
			return true
		}
	} else {
		return false
	}
}
