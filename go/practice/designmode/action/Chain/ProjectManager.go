/*
Package Chain

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Chain

import "fmt"

type ProjectManager struct{}

func NewProjectManager() *ProjectManager {
	return &ProjectManager{}
}

func NewProjectManagerChain() *RequestChain {
	return &RequestChain{&ProjectManager{}, nil}
}

func (p *ProjectManager) HaveRight(money int) bool {
	return money < 1000
}
func (p *ProjectManager) HandleFeeRequest(name string, money int) bool {
	if name == "Fee" {
		fmt.Printf("ProjectManager Handle FeeRequest %s %d\n", name, money)
		return true
	}
	return false
}
