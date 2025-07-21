/*
Package structure

	@author: June
	@since: 2025/7/20
	@desc: 代理模式
*/
package structure

import "fmt"

type Subject interface {
	Do() string
}

type RealSubject struct{}

func (RealSubject) Do() string {
	return "real"
}

type Proxy struct {
	real  RealSubject
	money int
}

func (p Proxy) Do() string {
	if p.money > 0 {
		return p.real.Do()
	} else {
		return "请充值"
	}
}

func main() {
	var sub Subject
	sub = &Proxy{money: 1}
	fmt.Println(sub.Do())
}
