/*
Package Decorator

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Decorator

/*Component @Description: 行为*/
type Component interface {
	Calc() int
}

type ConcreateComponent struct{}

func (c *ConcreateComponent) Calc() int {
	return 1
}
