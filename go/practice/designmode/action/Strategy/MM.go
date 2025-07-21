/*
Package Strategy

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Strategy

type MMContext struct {
	Name string
	Age  int
	Paox MMStrategy
}

func NewMMContext(name string, age int, pao MMStrategy) *MMContext {
	return &MMContext{name, age, pao}
}

func (c *MMContext) Pao() {
	c.Paox.Pao(c)
}

type MMStrategy interface {
	Pao(*MMContext)
}

type Girl struct{}

func (g *Girl) Pao(context *MMContext) {}

type Women struct{}

func (w *Women) Pao(context *MMContext) {}
