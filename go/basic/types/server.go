package types

type Service interface {
	DoSomething()
}

type myService struct{}

func (d *myService) DoSomething() {
	panic("implement me")
}

var DefaultService Service = &myService{}

func DoSomething() {
	DefaultService.DoSomething()
}
