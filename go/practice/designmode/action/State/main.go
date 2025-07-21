/*
Package State

	@author: June
	@since: 2025/7/20
	@desc:
*/
package State

func main() {
	ctx := NewDayContext()
	todayAndNext := func() {
		ctx.Today()
		ctx.Next()
	}
	for i := 0; i < 8; i++ {
		todayAndNext()
	}
}
