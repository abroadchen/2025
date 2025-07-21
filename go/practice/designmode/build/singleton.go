/*
Package designmode

	@author: June
	@since: 2025/7/20
	@desc:
*/
package build

import "sync"

type Single struct{}

var singleton *Single
var once sync.Once

func GetSingleton() *Single {
	once.Do(func() {
		singleton = &Single{}
	})
	return singleton
}
