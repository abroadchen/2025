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
	"github.com/gonum/matrix/mat64"
	"os"
	"strconv"
)

func predict(tv, radio, newspaper float64) float64 {
	return 3.038296 + 0.046537*tv + 0.177006*radio + 0.001088*newspaper
}

func main() {
	path := ""
	file, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	reader := csv.NewReader(file)
	reader.FieldsPerRecord = 4
	traindata, err := reader.ReadAll()
	//testdata, err := reader.ReadAll()
	if err != nil {
		fmt.Println(err)
	}
	//var mAE float64
	//for idx, record := range testdata {
	//	if idx == 0 {
	//		continue
	//	}
	//	yval, err := strconv.ParseFloat(record[3], 64)
	//	if err != nil {
	//		fmt.Println(err)
	//	}
	//	TVval, err := strconv.ParseFloat(record[0], 64)
	//	if err != nil {
	//		fmt.Println(err)
	//	}
	//	Rval, err := strconv.ParseFloat(record[1], 64)
	//	if err != nil {
	//		fmt.Println(err)
	//	}
	//	nval, err := strconv.ParseFloat(record[2], 64)
	//	if err != nil {
	//		fmt.Println(err)
	//	}
	//	ypredict := predict(TVval, Rval, nval)
	//	mAE += math.Abs(yval-ypredict) / float64(len(testdata))
	//}
	//fmt.Println(mAE)

	featureData := make([]float64, 4*len(traindata))
	yData := make([]float64, len(traindata))
	var featureindex int
	var yindex int
	for idx, record := range traindata {
		if idx == 0 {
			continue
		}
		for i, val := range record {
			valParsed, err := strconv.ParseFloat(val, 64)
			if err != nil {
				fmt.Println(err)
			}
			if i < 3 {
				if i == 0 {
					featureData[featureindex] = 1
					featureindex++
				}
				featureData[featureindex] = valParsed
				featureindex++
			}
			if i == 3 {
				yData[yindex] = valParsed
				yindex++
			}
		}
	}
	//创建矩阵
	features := mat64.NewDense(len(traindata), 4, featureData)
	y := mat64.NewVector(len(traindata), yData)
	fmt.Println(features, y)
}
