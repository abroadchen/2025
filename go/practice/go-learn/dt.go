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
	"github.com/sjwhitworth/golearn/ensemble"
	"github.com/sjwhitworth/golearn/evaluation"
	"math"
	"math/rand"
	"time"
)

func main() {
	path := ""
	irisdata, err := base.ParseCSVToInstances(path, true)
	if err != nil {
		fmt.Println(err)
	}
	rand.Seed(time.Now().UnixNano())
	//tree := trees.NewID3DecisionTree(0.6)
	tree := ensemble.NewRandomForest(10, 2)
	cv, err := evaluation.GenerateCrossFoldValidationConfusionMatrices(irisdata, tree, 5)
	if err != nil {
		fmt.Println(err)
	}
	mean, variance := evaluation.GetCrossValidatedMetric(cv, evaluation.GetAccuracy)
	stdev := math.Sqrt(variance)
	fmt.Println(mean, stdev)
}
