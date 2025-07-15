/*
Package viper

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package viper

import (
	"fmt"
	"github.com/syndtr/goleveldb/leveldb"
)

func main() {
	db, _ := leveldb.OpenFile("/tmp/leveldb", nil)
	defer db.Close()
	err := db.Put([]byte("hello"), []byte("world"), nil)
	if err != nil {
		panic(err)
	}
	data, err := db.Get([]byte("hello"), nil)
	fmt.Println(string(data))
	err = db.Delete([]byte("hello"), nil)
	iter := db.NewIterator(nil, nil)
	for iter.Next() {
		key := iter.Key()
		value := iter.Value()
		fmt.Println(string(key), string(value))
	}
	iter.Release()
	err = iter.Error()
}
