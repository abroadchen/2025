/*
Package Visitor

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Visitor

import "fmt"

type AnalysisVisitor struct{}

func (a *AnalysisVisitor) Visit(customer Customer) {
	switch customer.(type) {
	case *EnterpriseCustomer:
		fmt.Println("enterprise customer visitor")
		//case *IndividualCustomer:
		//	fmt.Println("individual customer visitor")
	}
}
