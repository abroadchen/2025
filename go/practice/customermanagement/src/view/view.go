package view

import (
	model "customermanagement/src/model"
	service "customermanagement/src/service"
	"fmt"
)

type CustomerView struct {
	key             string
	loop            bool
	customerService *service.CustomerService
}

func NewCustomerView() CustomerView {
	customerView := CustomerView{}
	customerView.loop = true
	customerView.customerService = service.NewCustomerService()
	return customerView
}

func (this *CustomerView) list() {
	customers := this.customerService.List()
	fmt.Println("-------------customerlist--------------")
	fmt.Println("编号\t姓名\t性别\t年龄\t电话\t邮箱")
	for i := 0; i < len(customers); i++ {
		fmt.Println(customers[i].GetInfo())
	}
	fmt.Println("-------------customerlist---------------\n\n")
}

func (this *CustomerView) add() {
	fmt.Println("---------------addcustomer-----------------------")
	fmt.Print("姓名:")
	name := ""
	fmt.Scanln(&name)
	fmt.Print("性别:")
	gender := ""
	fmt.Scanln(&gender)
	fmt.Print("年龄:")
	age := 0
	fmt.Scanln(&age)
	fmt.Print("电话:")
	phone := ""
	fmt.Scanln(&phone)
	fmt.Print("邮箱:")
	mail := ""
	fmt.Scanln(&mail)
	customer := model.NewCustomer2(name, gender, age, phone, mail)
	if this.customerService.Add(customer) {
		fmt.Println("-------------addsuccess----------------------")
	} else {
		fmt.Println("-------------addfail-----------------------")
	}
}

func (this *CustomerView) delete() {
	fmt.Println("--------------deletecustomer---------------")
	fmt.Print("please select (-1quit)")
	id := -1
	fmt.Scanln(&id)
	if id == -1 {
		return
	}
	fmt.Println("are you sure")
	choice := ""
	fmt.Scanln(&choice)
	if choice == "y" || choice == "Y" {
		if this.customerService.Delete(id) {
			fmt.Println("-------------deletesuccess--------------------")
		} else {
			fmt.Println("-------------deletefail----------------------")
		}
	}
}

func (this *CustomerView) MainMenu() {
	for {
		fmt.Println("---------------customerinformationmanagement----------------------")
		fmt.Println("------------------1 addcustomer----------------------------------")
		fmt.Println("---------------2 updatecustomer-----------------------")
		fmt.Println("--------------3 deletecustomer------------------")
		fmt.Println("--------------4 listcustomers--------------")
		fmt.Println("-------------- 5 quit--------------")
		fmt.Print("please select(1-5):")
		fmt.Scanln(&this.key)
		switch this.key {
		case "1":
			this.add()
		case "2":
			fmt.Println("update")
		case "3":
			this.delete()
		case "4":
			this.list()
		case "5":
			this.exit()
		default:
			fmt.Println("input err, please retry")
		}
		if !this.loop {
			break
		}
	}
	fmt.Println("--------------quit--------------")
}

func (this *CustomerView) exit() {
	fmt.Print("are you sure to quit(Y/N")
	for {
		fmt.Scanln(&this.key)
		if this.key == "y" || this.key == "Y" || this.key == "N" || this.key == "n" {
			break
		}
		fmt.Print("input err, please retry")
	}
	if this.key == "Y" || this.key == "y" {
		this.loop = false
	}
}
