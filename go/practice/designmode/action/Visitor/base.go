/*
Package Visitor

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Visitor

type Customer interface {
	Accept(Visitor)
}

type Visitor interface {
	Visit(Customer)
}
