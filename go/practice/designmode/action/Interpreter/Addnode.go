/*
Package Interpreter

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Interpreter

type AddNode struct {
	left, right Node
}

func (a *AddNode) Interpret() int {
	return a.left.Interpret() + a.right.Interpret()
}
