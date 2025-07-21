/*
Package build

	@author: June
	@since: 2025/7/20
	@desc:
*/
package build

import "fmt"

type Builder interface {
	Part1()
	Part2()
}

type Director struct {
	builder Builder
}

func NewDirector(builder Builder) *Director {
	return &Director{builder}
}

func (d *Director) Construct() {
	d.builder.Part1()
	d.builder.Part2()
}

type StringBuilder struct {
	result string
}

func (sb *StringBuilder) Part1() {
	sb.result += "1"
}
func (sb *StringBuilder) Part2() {
	sb.result += "2"
}
func (sb *StringBuilder) GetResult() string {
	return sb.result
}

type IntBuilder struct {
	result int64
}

func main() {
	builder := &StringBuilder{}
	dict := NewDirector(builder)
	dict.Construct()
	fmt.Println(builder.GetResult())
}
