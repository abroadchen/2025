/*
Package go_learn

	@author: June
	@since: 2025/7/20
	@desc:
*/
package go_learn

import (
	"fmt"
	"github.com/go-gota/gota/dataframe"
	"os"
)

func main() {
	path := "test.csv"
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	irisDF := dataframe.ReadCSV(file)
	fmt.Println(irisDF)
	filter := dataframe.F{
		Colname:    "species",
		Comparator: "==",
		Comparando: "Iris-setosa",
	}
	fmt.Println(filter)
	mydf := irisDF.Filter(filter)
	fmt.Println(mydf)

	newdf := irisDF.Filter(filter).Select([]string{"petal_length", "petal_width"}).Subset([]int{0, 1, 2})
	fmt.Println(newdf)
}
