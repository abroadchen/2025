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
	"github.com/sjwhitworth/golearn/knn"
	"math"
)

func main() {
	path := ""
	irisdata, err := base.ParseCSVToInstances(path, true)
	if err != nil {
		fmt.Println(err)
	}
	knn := knn.NewKnnClassifier("euclidean", "linear", 2)
	cv, err := evaluation.GenerateCrossFoldValidationConfusionMatrices(irisdata, knn, 5)
	if err != nil {
		fmt.Println(err)
	}
	mean, variance := evaluation.GetCrossValidatedMetric(cv, evaluation.GetAccuracy)
	stdev := math.Sqrt(variance)
	fmt.Println(mean, stdev)
}
