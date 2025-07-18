/*
Package jsonxmltemplate

	@author: June
	@since: 2025/7/18
	@desc:
*/
package jsonxmltemplate

import (
	"fmt"
	"github.com/bitly/go-simplejson"
)

func main() {
	js, err := simplejson.NewJson([]byte(`{
		"test": {
			"array": [1, "2", 3],
			"int": 10,
			"float": 3.14,
			"bignum": 22222222222222,
			"string": "hello world",
			"bool": true
		}
	}`))

	if err != nil {
		fmt.Println(err)
	}

	arr, _ := js.Get("test").Get("array").Array()
	i, _ := js.Get("test").Get("int").Int()
	ms := js.Get("test").Get("string").MustString()

	fmt.Println(ms)
	fmt.Println(i)
	fmt.Println(arr)
}
