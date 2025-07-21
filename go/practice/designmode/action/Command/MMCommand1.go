/*
Package Command

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Command

type MMCommand1 struct {
	mb *MotherBoard
}

func NewMMCommand1(mb *MotherBoard) *MMCommand1 {
	return &MMCommand1{mb: mb}
}

func (m *MMCommand1) Execute() {
	m.mb.WashClothes()
}
