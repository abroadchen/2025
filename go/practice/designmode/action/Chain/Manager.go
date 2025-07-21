/*
Package Chain

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Chain

type Manager interface {
	HaveRight(money int) bool
	HandleFeeRequest(name string, money int) bool
}
