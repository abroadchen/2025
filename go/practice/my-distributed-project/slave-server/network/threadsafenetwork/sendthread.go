package threadsafenetwork

import (
	"net"
	"sync"
)

type ReturnEmail struct {
	conn  net.Conn
	mutex *sync.Mutex
}

func NewReturnEmail(conn net.Conn) *ReturnEmail {
	myr := new(ReturnEmail)
	myr.conn = conn
	myr.mutex = new(sync.Mutex)
	return myr
}

func (r *ReturnEmail) SaveMail(mail string) {
	r.mutex.Lock()
	mystr := mail
	mystrlen := len(mystr)
	mybytes := IntToBytes(mystrlen)
	r.conn.Write(mybytes)
	r.conn.Write([]byte(mystr))
	r.mutex.Unlock()
}

func (r *ReturnEmail) SaveMails(mails []string) {
	r.mutex.Lock()
	for _, mail := range mails {
		mystr := mail
		mystrlen := len(mystr)
		mybytes := IntToBytes(mystrlen)
		r.conn.Write(mybytes)
		r.conn.Write([]byte(mystr))
	}
	r.mutex.Unlock()
}
