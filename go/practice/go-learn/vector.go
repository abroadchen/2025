/*
Package go_learn

	@author: June
	@since: 2025/7/20
	@desc:
*/
package go_learn

import (
	"fmt"
	"github.com/gonum/floats"
	"github.com/gonum/matrix/mat64"
)

func main() {
	var myv []float64
	myv = append(myv, 1.0)
	myv = append(myv, 2.0)
	myv = append(myv, 3.0)
	fmt.Println(myv)

	myv2 := mat64.NewVector(3, []float64{1, 2, 3})
	fmt.Println(myv2)

	vA := []float64{1, 2, 3}
	vB := []float64{1, 2, 3}
	fmt.Println("dot product", floats.Dot(vA, vB))
	floats.Scale(2, vA)
	fmt.Println(vA)
	normB := floats.Norm(vB, 2)
	fmt.Println(normB)

	vA2 := mat64.NewVector(3, []float64{1, 2, 3})
	vB2 := mat64.NewVector(3, []float64{1, 2, 3})
	fmt.Println("dot product", mat64.Dot(vA2, vB2))
	vA2.ScaleVec(3, vA2)
	fmt.Println(vA2)
}
