/*
Package designmode

	@author: June
	@since: 2025/7/20
	@desc:
*/
package build

type Operator interface {
	Setleft(int)
	Setright(int)
	Result() int
}

type OperatorFactory interface {
	Create() Operator
}

type OperatorBase struct {
	left, right int
}

func (op *OperatorBase) Setleft(left int) {
	op.left = left
}

func (op *OperatorBase) Setright(right int) {
	op.right = right
}

type PlusOperatorFactory struct{}
type PlusOperator struct {
	*OperatorBase
}

func (o PlusOperator) Result() int {
	return o.left + o.right
}

func (PlusOperatorFactory) Create() Operator {
	return &PlusOperator{&OperatorBase{}}
}

type SubOperatorFactory struct{}

type SubOperator struct {
	*OperatorBase
}

func (o SubOperator) Result() int {
	return o.left - o.right
}

func (SubOperatorFactory) Create() Operator {
	return &SubOperator{&OperatorBase{}}
}

func main() {
	var fac OperatorFactory
	fac = PlusOperatorFactory{}
	op := fac.Create()
	op.Setleft(3)
	op.Setright(4)
}
