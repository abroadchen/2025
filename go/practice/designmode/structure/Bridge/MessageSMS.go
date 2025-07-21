/*
Package Bridge

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Bridge

import "fmt"

type MessageSMS struct{}

func (m MessageSMS) Send(text, to string) {
	//TODO implement me
	fmt.Printf("send %s to %s via SMS\n", text, to)
}

func ViaSMS() MessageImpl {
	return &MessageSMS{}
}
