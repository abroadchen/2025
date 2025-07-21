/*
Package State

	@author: June
	@since: 2025/7/20
	@desc:
*/
package State

type Week interface {
	Today()
	Next(*DayContext)
}

type DayContext struct {
	today Week
}

func NewDayContext() *DayContext {
	return &DayContext{&Sunday{}}
}

func (d *DayContext) Today() {
	d.today.Today()
}
func (d *DayContext) Next() {
	d.today.Next(d)
}
