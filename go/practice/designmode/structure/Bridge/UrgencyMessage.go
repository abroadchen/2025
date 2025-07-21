/*
Package Bridge

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Bridge

import "fmt"

type UrgencyMessage struct {
	method MessageImpl
}

func NewUrgencyMessage(method MessageImpl) *UrgencyMessage {
	return &UrgencyMessage{method: method}
}

func (m *UrgencyMessage) SendMessage(text, to string) {
	m.method.Send(fmt.Sprintf("发送到[%s]", text), to)
}
