/*
Package go_learn

	@author: June
	@since: 2025/7/21
	@desc:
*/
package go_learn

import (
	"fmt"
	"github.com/go-gota/gota/dataframe"
	"github.com/gonum/floats"
	"gonum.org/v1/gonum/stat"
	"os"
)

func main() {
	path := "x.csv"
	irisfile, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer irisfile.Close()

	irisDF := dataframe.ReadCSV(irisfile)
	seplen := irisDF.Col("petal_length").Float()
	meanVal := stat.Mean(seplen, nil)
	fmt.Println(meanVal)

	modeVal, modeCount := stat.Mode(seplen, nil)
	fmt.Println(modeVal, modeCount)

	fmt.Println("min", floats.Min(seplen))
	fmt.Println("max", floats.Max(seplen))
	fmt.Println("range", floats.Max(seplen)-floats.Min(seplen))
	fmt.Println("variance", stat.Variance(seplen, nil))
	fmt.Println("stddev", stat.StdDev(seplen, nil))

	inds := make([]int, len(seplen))
	floats.Argsort(seplen, inds)
	q25 := stat.Quantile(0.25, stat.Empirical, seplen, nil)
	q50 := stat.Quantile(0.5, stat.Empirical, seplen, nil)
	q75 := stat.Quantile(0.75, stat.Empirical, seplen, nil)
	fmt.Println(q25, q50, q75)
}
