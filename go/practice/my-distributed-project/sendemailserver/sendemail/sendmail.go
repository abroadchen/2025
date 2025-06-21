package sendemail

import (
	"github.com/go-gomail/gomail"
)

type SendEmail struct {
	msg      *gomail.Message
	sender   string
	receive  []string
	topic    string
	content  string
	user     string
	password string
	filepath string
	sendname string
	host     string
	port     int
}

func NewSendEmail(host string, port int, sender string, topic string, content string, user string, pwd string, filepath string, sendname string, receive ...string) *SendEmail {
	m := gomail.NewMessage()
	m.SetHeader("From", sender)
	m.SetHeader("To", receive...)
	m.SetAddressHeader("Cc", sender, sendname)
	m.SetHeader("Subject", topic)
	m.SetBody("text/html", content)
	m.Attach(filepath)
	mysend := new(SendEmail)
	mysend.msg = m
	mysend.user = user
	mysend.password = pwd
	mysend.receive = receive
	return mysend
}

func (send *SendEmail) Send() bool {
	d := gomail.NewDialer(send.host, send.port, send.user, send.password)
	if err := d.DialAndSend(send.msg); err != nil {
		return false
	} else {
		return true
	}
}
