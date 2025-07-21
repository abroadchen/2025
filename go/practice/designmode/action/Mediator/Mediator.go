/*
Package Mediator

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Mediator

type Mediator struct {
	Cpu  *CPU
	Disk *Disk
	Gpu  *GPU
	Mem  *MEM
}

var mediator *Mediator

func GetMediatorInstance() *Mediator {
	if mediator == nil {
		mediator = &Mediator{}
	}
	return mediator
}

func (m *Mediator) changed(i interface{}) {
	switch t := i.(type) {
	case *CPU:
		m.Cpu.process(t.data)
	case *Disk:
		m.Disk.Store(t.data)
	case *GPU:
		m.Gpu.Display(t.data)
	case *MEM:
		m.Mem.Dump(t.data)
	default:
	}
}
