package main

import (
	"context"
	"fmt"
	"github.com/redis/go-redis/v9"
	"log"
	"time"
)

var ctx = context.Background()

func ExampleClient() {
	rdb := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "",
		DB:       0,
	})

	err := rdb.Set(ctx, "key", "value", 0).Err()
	if err != nil {
		log.Fatal(err)
	}

	val, err := rdb.Get(ctx, "key").Result()
	if err != nil {
		log.Fatal(val, err)
	}

	val2, err := rdb.Get(ctx, "key2").Result()
	if err == redis.Nil {
		fmt.Println("key2 does not exist")
	} else if err != nil {
		log.Fatal(val2, err)
	}

	set, err := rdb.SetNX(ctx, "key", "value", 10*time.Second).Result()
	fmt.Println(set, err)
	set, err = rdb.SetNX(ctx, "key", "value", redis.KeepTTL).Result()
	fmt.Println(set, err)
	vals, err := rdb.Sort(ctx, "list", &redis.Sort{
		Offset: 0,
		Count:  2,
		Order:  "ASC",
	}).Result()
	fmt.Println(vals, err)
	vals, err = rdb.ZRangeByScoreWithScores(ctx, "zset", &redis.ZRangeBy{
		Min:    "-inf",
		Max:    "+inf",
		Offset: 0,
		Count:  2,
	}).Result()
	fmt.Println(vals, err)
	vals, err = rdb.ZInterStore(ctx, "out", &redis.ZStore{
		Keys:    []string{"zset1", "zset2"},
		Weights: []int64{2, 3},
	}).Result()
	fmt.Println(vals, err)
	vals, err = rdb.Eval(ctx, "return {KEYS[1],ARGV[1]}", []string{"key"}, "").Result()
	fmt.Println(vals, err)
	res, err := rdb.Do(ctx, "return {KEYS[1],ARGV[1]}", []string{"key"}, "").Result()
	fmt.Println(res, err)
}
