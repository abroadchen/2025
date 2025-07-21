/*
Package structure

	@author: June
	@since: 2025/7/20
	@desc: 适配器模式
*/
package structure

import "fmt"

type Target interface {
	Request() string
}

type adapter struct {
	Adaptee
}

func NewAdapter(adaptee Adaptee) Target {
	return &adapter{adaptee}
}

func (adap *adapter) Request() string {
	return adap.SpecficRequest()
}

type Adaptee interface {
	SpecficRequest() string
}
type adapteeImpl struct{}

func (a adapteeImpl) SpecficRequest() string {
	//TODO implement me
	panic("implement me")
}

func NewAdaptee() Adaptee {
	return &adapteeImpl{}
}

func main() {
	adapee := NewAdaptee()
	target := NewAdapter(adapee)
	res := target.Request()
	fmt.Println(res)
}
