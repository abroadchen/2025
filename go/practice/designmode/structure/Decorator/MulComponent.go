/*
Package Decorator

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Decorator

type MulComponent struct {
	Component
	num int
}

func (m *MulComponent) Calc() int {
	//TODO implement me
	return m.Component.Calc() * m.num
}

func WarpMulComponent(c Component, num int) Component {
	return &MulComponent{c, num}
}
