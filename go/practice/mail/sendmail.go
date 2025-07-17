/*
Package mail

	@author: chen
	@since: 2025/7/16
	@desc:  https://pkg.go.dev/gopkg.in/gomail.v2
*/
package mail

import (
	"github.com/go-gomail/gomail"
	"log"
	"os"
	"time"
)

func main11() {
	m := gomail.NewMessage()
	m.SetHeader("From", "<"+os.Getenv("MAIL_FROM")+">")
	m.SetHeader("To", "<"+os.Getenv("MAIL_TO")+">")
	m.SetAddressHeader("Cc", "", "")
	m.SetHeader("Subject", "Hello")
	m.SetBody("text/html", "Hello World")
	m.Attach("./mail/mail.txt")

	d := gomail.NewDialer("smtp.163.com", 25, os.Getenv("MAIL_FROM"), os.Getenv("MAIL_TO"))
	if err := d.DialAndSend(m); err != nil {
		panic(err)
	}
}

func main() {
	ch := make(chan *gomail.Message)

	go func() {
		d := gomail.NewDialer("smtp.example.com", 587, "user", "123456")

		var s gomail.SendCloser
		var err error
		open := false
		for {
			select {
			case m, ok := <-ch:
				if !ok {
					return
				}
				if !open {
					if s, err = d.Dial(); err != nil {
						panic(err)
					}
					open = true
				}
				if err := gomail.Send(s, m); err != nil {
					log.Print(err)
				}
			// Close the connection to the SMTP server if no email was sent in
			// the last 30 seconds.
			case <-time.After(30 * time.Second):
				if open {
					if err := s.Close(); err != nil {
						panic(err)
					}
					open = false
				}
			}
		}
	}()

	// Use the channel in your program to send emails.

	// Close the channel to stop the mail daemon.
	close(ch)
}
