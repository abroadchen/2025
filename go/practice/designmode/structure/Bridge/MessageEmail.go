/*
Package Bridge

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Bridge

import "fmt"

type MessageEmail struct{}

func (m MessageEmail) Send(text, to string) {
	//TODO implement me
	fmt.Printf("send %s to %s via Email\n", text, to)
}

func ViaEmail() MessageImpl {
	return &MessageEmail{}
}
