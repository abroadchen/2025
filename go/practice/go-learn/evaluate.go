/*
Package go_learn

	@author: June
	@since: 2025/7/21
	@desc:
*/
package go_learn

import (
	"encoding/csv"
	"fmt"
	"github.com/gonum/stat"
	"gonum.org/v1/gonum/integrate"
	"io"
	"math"
	"os"
	"strconv"
)

func main() {
	path := os.Args[1]
	file, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	reader := csv.NewReader(file)
	var observed []float64
	var predict []float64
	line := 1
	for {
		record, err := reader.Read()
		if err == io.EOF {
			break
		}
		if line == 1 {
			line++
			continue
		}
		//obval, err := strconv.Atoi(record[0])
		obval, err := strconv.ParseFloat(record[0], 64)
		if err != nil {
			fmt.Println(err)
			continue
		}
		predictval, err := strconv.ParseFloat(record[1], 64)
		if err != nil {
			fmt.Println(err)
			continue
		}
		observed = append(observed, obval)
		predict = append(predict, predictval)
		line++
	}
	//  统计连续指标
	var mAE float64
	var mSE float64
	for idx, oVal := range observed {
		mAE += math.Abs(oVal-predict[idx]) / float64(len(observed))
		mSE += math.Pow(oVal-predict[idx], 2) / float64(len(observed))
	}
	fmt.Println(mAE, mSE)

	rs := stat.RSquaredFrom(observed, predict, nil)
	fmt.Println(rs)

	// 统计分类指标
	//classes := []int{0, 1, 2}
	//
	//for _, class := range classes {
	//	var truePos int
	//	var falsePos int
	//	var falseNeg int
	//
	//	for idx, oVal := range observed {
	//		switch oVal {
	//		case class:
	//			if predict[idx] == class {
	//				truePos++
	//				continue
	//			}
	//			falseNeg++
	//		default:
	//			if predict[idx] == class {
	//				falsePos++
	//			}
	//		}
	//	}
	//	precision := float64(truePos) / float64(falsePos+truePos)
	//	recall := float64(truePos) / float64(truePos+falseNeg)
	//	fmt.Println(class, precision, recall)
	//}

	//var truePosNeg int
	//for idx, oval := range observed {
	//	if oval == predict[idx] {
	//		truePosNeg++
	//	}
	//}
	//accuracy := float64(truePosNeg) / float64(len(observed))
	//fmt.Println(accuracy)

	scores := []float64{0.1, 0.35, 0.4, 0.8}
	classes2 := []bool{true, false, true, false}
	tpr, fpr := stat.ROC(0, scores, classes2, nil)
	auc := integrate.Trapezoidal(tpr, fpr)
	fmt.Println(tpr, auc)
}
