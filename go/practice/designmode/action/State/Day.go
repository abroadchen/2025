/*
Package State

	@author: June
	@since: 2025/7/20
	@desc:
*/
package State

import "fmt"

type Sunday struct{}

func (sd *Sunday) Today() {
	fmt.Println("Sunday")
}

func (sd *Sunday) Next(ctx *DayContext) {
	ctx.today = &Monday{}
}

type Monday struct{}

func (m Monday) Today() {
	//TODO implement me
	panic("implement me")
}

func (m Monday) Next(context *DayContext) {
	//TODO implement me
	panic("implement me")
}
