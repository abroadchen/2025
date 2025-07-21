/*
Package designmode

	@author: June
	@since: 2025/7/20
	@desc:
*/
package build

import "fmt"

type Clonable interface {
	Clone() Clonable
}

type PrototypeManager struct {
	prototypes map[string]Clonable
}

func NewPrototypeManager() *PrototypeManager {
	return &PrototypeManager{
		prototypes: make(map[string]Clonable),
	}
}
func (p *PrototypeManager) Get(name string) Clonable {
	return p.prototypes[name]
}
func (p *PrototypeManager) Set(name string, prototype Clonable) {
	p.prototypes[name] = prototype
}

type Type1 struct {
	name string
}

func (t *Type1) Clone() Clonable {
	//tc := *t
	//return &tc
	return t
}

type Type2 struct {
	name string
}

func (t *Type2) Clone() Clonable {
	tc := *t
	return &tc
}

func main() {
	mgr := NewPrototypeManager()
	t1 := &Type1{"t1"}
	mgr.Set(t1.name, t1)
	t11 := mgr.Get("t1")
	t22 := t11.Clone()
	if t11 == t22 {
		fmt.Println("浅拷贝")
	} else {
		fmt.Println("深拷贝")
	}
}
