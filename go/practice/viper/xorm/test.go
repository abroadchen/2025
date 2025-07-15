/*
Package xorm

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package xorm

import (
	"fmt"
	"github.com/go-xorm/xorm"
	"os"
)

var engine *xorm.Engine

func main() {
	var err error
	engine, err = xorm.NewEngine("mysql", "root:@tcp(127.0.0.1:3306)/test?charset=utf8")
	fmt.Println(err)

	f, err := os.Create("sql.log")
	if err != nil {
		fmt.Println(err)
		return
	}
	engine.SetLogger(xorm.NewSimpleLogger(f))
}
