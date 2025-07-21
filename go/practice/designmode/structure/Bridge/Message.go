/*
Package Bridge

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Bridge

/*AbstractMessage @Description: 特快 普通*/
type AbstractMessage interface {
	SendMessage(text, to string)
}

/*MessageImpl @Description: 短信 邮件*/
type MessageImpl interface {
	Send(text, to string)
}
