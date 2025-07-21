/*
Package Visitor

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Visitor

type EnterpriseCustomer struct {
	name string
}

func NewEnterpriseCustomer(name string) *EnterpriseCustomer {
	return &EnterpriseCustomer{name: name}
}

func (c *EnterpriseCustomer) Accept(visitor Visitor) {
	visitor.Visit(c)
}
