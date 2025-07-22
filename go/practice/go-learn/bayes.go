/*
Package go_learn

	@author: June
	@since: 2025/7/21
	@desc:
*/
package go_learn

import (
	"fmt"
	"github.com/sjwhitworth/golearn/base"
	"github.com/sjwhitworth/golearn/evaluation"
	"github.com/sjwhitworth/golearn/filters"
	"github.com/sjwhitworth/golearn/naive"
)

func convert2Binary(src base.FixedDataGrid) base.FixedDataGrid {
	b := filters.NewBinaryConvertFilter()
	attrs := base.NonClassAttributes(src)
	for _, a := range attrs {
		b.AddAttribute(a)
	}
	b.Train()
	ret := base.NewLazilyFilteredInstances(src, b)
	return ret
}

func main() {
	path := ""
	traindata, err := base.ParseCSVToInstances(path+"training.csv", true)
	if err != nil {
		fmt.Println(err)
	}
	nb := naive.NewBernoulliNBClassifier()
	nb.Fit(convert2Binary(traindata))
	testdata, err := base.ParseCSVToInstances(path+"test.csv", true)
	if err != nil {
		fmt.Println(err)
	}
	predicted, err := nb.Predict(convert2Binary(testdata))
	if err != nil {
		fmt.Println(err)
	}
	cm, err := evaluation.GetConfusionMatrix(testdata, predicted)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(evaluation.GetAccuracy(cm))
}
