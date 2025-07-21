/*
Package designmode

	@author: June
	@since: 2025/7/20
	@desc:
*/
package build

import "fmt"

type API interface {
	Say(name string) string
}

func NewAPI(str string) API {
	if str == "en" {
		return &English{}
	} else if str == "zh" {
		return &Chinese{}
	} else {
		return nil
	}
}

type Chinese struct{}

func (c *Chinese) Say(name string) string { return " " }

type English struct{}

func (e *English) Say(name string) string { return " " }

func main() {
	api := NewAPI("en")
	server := api.Say("")
	fmt.Println(server)
}
