/*
Package Chain

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Chain

type RequestChain struct {
	Manager
	successor *RequestChain
}

func (rc *RequestChain) SetSuccessor(successor *RequestChain) {
	rc.successor = successor
}

func (rc *RequestChain) HaveRight(money int) bool {
	return true
}

func (rc *RequestChain) HandleFeeRequest(name string, money int) bool {
	if rc.Manager.HaveRight(money) {
		return rc.Manager.HandleFeeRequest(name, money)
	}
	if rc.successor != nil {
		return rc.successor.HandleFeeRequest(name, money)
	}
	return false
}
