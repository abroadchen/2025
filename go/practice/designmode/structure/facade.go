/*
Package structure

	@author: June
	@since: 2025/7/20
	@desc: 外观模式
*/
package structure

import "fmt"

type API interface {
	Test() string
}

func NewAPI() API {
	return &APICall{NewAmoudleAPI(), NewBMoudleAPI()}
}

type AmoudleAPI interface {
	TestA() string
}
type aMoudleImpl struct{}

func (a aMoudleImpl) TestA() string {
	//TODO implement me
	panic("implement me")
}

func NewAmoudleAPI() AmoudleAPI {
	return &aMoudleImpl{}
}

type BmoudleAPI interface {
	TestB() string
}
type bMoudleImpl struct{}

func (b bMoudleImpl) TestB() string {
	//TODO implement me
	panic("implement me")
}

func NewBMoudleAPI() BmoudleAPI {
	return &bMoudleImpl{}
}

type APICall struct {
	a AmoudleAPI
	b BmoudleAPI
}

func (api *APICall) Test() string {
	return fmt.Sprintf("%s\n%s", api.a.TestA(), api.b.TestB())
}
