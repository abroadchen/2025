package main

import (
	model2 "customermanagement/src/model"
	service "customermanagement/src/service"
	view "customermanagement/src/view"
	"fmt"
)

func main() {

	mylist := service.NewCustomerService()
	c1 := model2.NewCustomer(10, "test", "女", 18, "13935465587", "123@163.com")
	fmt.Println(c1.GetInfo())
	mylist.Add(c1)
	mycustomlist := mylist.List()
	for _, v := range mycustomlist {
		fmt.Println(v.GetInfo())
	}
	customerView := view.NewCustomerView()

	customerView.MainMenu()
}
