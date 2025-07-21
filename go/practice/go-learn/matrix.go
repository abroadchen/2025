/*
Package go_learn

	@author: June
	@since: 2025/7/21
	@desc:
*/
package go_learn

import (
	"fmt"
	"github.com/gonum/matrix/mat64"
)

func main() {
	data := []float64{1, 2, 3, 4, 5}
	a := mat64.NewDense(3, len(data), data)
	fa := mat64.Formatted(a, mat64.Prefix("    "))
	fmt.Println(fa)

	val := a.At(0, 0)
	fmt.Println(val)
	col := mat64.Col(nil, 0, a)
	fmt.Println(col)
	row := mat64.Row(nil, 0, a)
	fmt.Println(row)

	a.Set(0, 0, 1)
	fmt.Println(a.At(0, 0))

	a.SetRow(0, row)
	fmt.Println(fa)
	a.SetCol(0, col)
	fmt.Println(fa)

	ft := mat64.Formatted(a.T(), mat64.Prefix(""))
	fmt.Println(ft)
	fmt.Println(mat64.Det(a)) //行列式

	ai := mat64.NewDense(0, 0, nil)
	if err := ai.Inverse(a); err != nil {
		panic(err)
	}
	fi := mat64.Formatted(ai, mat64.Prefix("    "))
	fmt.Println(fi)
}
