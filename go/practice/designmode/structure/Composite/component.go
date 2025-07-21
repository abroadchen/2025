/*
Package Composite

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Composite

type Component interface {
	Parent() Component
	SetParent(Component)
	Name() string
	SetName(string)
	AddChild(Component)
	Print(string)
}

const (
	LeafNode = iota
	CompositeNode
)

type component struct {
	parent Component
	name   string
}

func NewComponent(kind int, name string) Component {
	var c component
	switch kind {
	case LeafNode:
		c = NewLeaf().component
	case CompositeNode:
		c = NewComposite().component
	}
	c.SetName(name)
	return &c
}

func (c *component) Parent() Component {
	return c.parent
}
func (c *component) SetParent(parent Component) {
	c.parent = parent
}
func (c *component) Name() string {
	return c.name
}
func (c *component) AddChild(child Component) {}
func (c *component) Print(text string)        {}
func (c *component) SetName(name string) {
	c.name = name
}

func main() {
	root := NewComponent(CompositeNode, "root")
	r1 := NewComponent(CompositeNode, "r1")
	r2 := NewComponent(CompositeNode, "r2")

	l1 := NewComponent(LeafNode, "l1")
	l2 := NewComponent(LeafNode, "l2")

	root.AddChild(r1)
	r1.AddChild(r2)
	r1.AddChild(l1)
	r2.AddChild(l2)
}
