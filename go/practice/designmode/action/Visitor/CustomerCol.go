/*
Package Visitor

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Visitor

type CustomerCol struct {
	Customers []Customer
}

func (c *CustomerCol) Add(customer Customer) {
	c.Customers = append(c.Customers, customer)
}

func (c *CustomerCol) Accept(visitor Visitor) {
	for _, customer := range c.Customers {
		customer.Accept(visitor)
	}
}
