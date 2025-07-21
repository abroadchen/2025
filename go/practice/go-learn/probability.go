/*
Package go_learn

	@author: June
	@since: 2025/7/21
	@desc:
*/
package go_learn

import (
	"fmt"
	"gonum.org/v1/gonum/stat"
	"gonum.org/v1/gonum/stat/distuv"
)

func main() {
	ob := []float64{260, 135, 105}
	total := 500.0
	ex := []float64{total * 0.6, total * 0.25, total * 0.15} //期望值
	fmt.Println(stat.ChiSquare(ob, ex))

	chiDist := distuv.ChiSquared{
		K: 2.0,
	}
	fmt.Println(chiDist.Prob(stat.ChiSquare(ob, ex)))
}
