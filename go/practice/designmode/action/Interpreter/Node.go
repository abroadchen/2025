/*
Package Interpreter

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Interpreter

type Node interface {
	Interpret() int
}
type ValNode struct {
	val int
}

func (n *ValNode) Interpret() int {
	return n.val
}
