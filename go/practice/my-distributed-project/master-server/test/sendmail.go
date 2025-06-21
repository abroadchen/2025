package test

import (
	"fmt"
)
import "gopkg.in/gomail.v2"

func main() {
	m := gomail.NewMessage()
	m.SetHeader("From", "admin@example.com")
	m.SetHeader("To", "admin@example.com", "")
	m.SetAddressHeader("Cc", "", "")
	m.SetHeader("Subject", "admin@example.com")
	m.SetBody("text/html", "Hello World!")
	m.Attach("")
	d := gomail.NewDialer("smtp.example.com", 25, "admin@example.com", "password")
	if err := d.DialAndSend(m); err != nil {
		fmt.Println(err)
	} else {
		fmt.Println("send mail success")
	}
}
