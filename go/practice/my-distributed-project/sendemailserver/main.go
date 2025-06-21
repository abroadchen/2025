package sendemailserver

import "sendemailserver/nsq"

func main() {
	nsq.NSQThread()
}
