/*
Package Composite

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Composite

import "fmt"

type Leaf struct {
	component
}

func NewLeaf() *Leaf {
	return &Leaf{}
}

func (c *Leaf) Print(pre string) {
	fmt.Println(pre, c.Name())
}

type Composite struct {
	component
	childs []Component
}

func NewComposite() *Composite {
	return &Composite{
		childs: make([]Component, 0),
	}
}

func (c *Composite) AddChild(child Component) {
	child.SetParent(c)
	c.childs = append(c.childs, child)
}
func (c *Composite) Print(text string) {
	fmt.Printf("%s %s\n", c.name, text)
	text += " "
	for _, child := range c.childs {
		child.Print(text)
	}
}
