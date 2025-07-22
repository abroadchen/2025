/*
Package go_learn

	@author: June
	@since: 2025/7/21
	@desc:
*/
package go_learn

import (
	"bufio"
	"encoding/csv"
	"fmt"
	"github.com/go-gota/gota/dataframe"
	"github.com/gonum/matrix/mat64"
	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
	"image/color"
	"io"
	"math"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"
)

func logistc(x float64) float64 {
	return 1 / (1 + math.Exp(-x))
}

func maindraw() {
	p := plot.New()
	p.Title.Text = "Logistc Model"
	p.X.Label.Text = "x"
	p.Y.Label.Text = "f(x)"

	myp := plotter.NewFunction(func(x float64) float64 {
		return logistc(x)
	})
	myp.Color = color.RGBA{0, 255, 0, 255}
	p.Add(myp)
	p.X.Min = -10
	p.X.Max = 10
	p.Y.Min = -0.1
	p.Y.Max = 1.1

	if err := p.Save(4*vg.Inch, 4*vg.Inch, "logistc.png"); err != nil {
		fmt.Println(err)
	}
}

func main() {
	path := ""
	file, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()
	reader := csv.NewReader(file)
	reader.FieldsPerRecord = 2
	rawcsvdata, err := reader.ReadAll()
	if err != nil {
		fmt.Println(err)
	}
	savefile, err := os.Create(path + "load_clean_data.csv")
	if err != nil {
		fmt.Println(err)
	}
	defer savefile.Close()
	w := csv.NewWriter(savefile)
	for idx, record := range rawcsvdata {
		if idx == 0 {
			if err := w.Write([]string{"FICO_socre", "class"}); err != nil {
				fmt.Println(err)
			}
			continue
		}
		outRecord := make([]string, 2)
		score, err := strconv.ParseFloat(strings.Split(record[0], "-")[0], 64)
		if err != nil {
			fmt.Println(err)
		}
		outRecord[0] = strconv.FormatFloat((score-640.0)/(830.0-640.0), 'f', 4, 64)
		rate, err := strconv.ParseFloat(strings.TrimSuffix(record[1], "%"), 64)
		if err != nil {
			fmt.Println(err)
		}
		if rate <= 12.0 {
			outRecord[1] = "1.0"
			if err := w.Write(outRecord); err != nil {
				fmt.Println(err)
			}
			continue
		}
		outRecord[1] = "0.0"
		if err := w.Write(outRecord); err != nil {
			fmt.Println(err)
		}
	}
	w.Flush()
}

func maindraw2() {
	path := ""
	file, err := os.Open(path + "load_clean_data.csv")
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	loadDF := dataframe.ReadCSV(file)
	for _, colName := range loadDF.Names() {
		//plotvals := make(plotter.Values, adDF.Nrow())
		plotvals := make(plotter.Values, loadDF.Nrow())
		for i, floatval := range loadDF.Col(colName).Float() {
			//plotvals[i] = floatval
			plotvals[i] = floatval
		}

		p := plot.New()
		if err != nil {
			fmt.Println(err)
		}

		p.X.Label.Text = colName
		p.Y.Label.Text = "y"
		p.Title.Text = fmt.Sprintf("histogram of %d", colName)
		h, err := plotter.NewHist(plotvals, 16)
		if err != nil {
			fmt.Println(err)
		}
		h.Normalize(1)
		p.Add(h)

		if err := p.Save(4*vg.Inch, 4*vg.Inch, colName+"hist.png"); err != nil {
			fmt.Println(err)
		}
	}
}

func mainsplit() {
	path := ""
	file, err := os.Open(path + "load_clean_data.csv")
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	loadDF := dataframe.ReadCSV(file)
	trainNum := (4 * loadDF.Nrow()) / 5
	testNum := loadDF.Nrow() / 5
	if trainNum+testNum < loadDF.Nrow() {
		trainNum++
	}
	trainIdx := make([]int, trainNum)
	testIdx := make([]int, testNum)
	for i := 0; i < trainNum; i++ {
		trainIdx[i] = i
	}
	for i := 0; i < testNum; i++ {
		testIdx[i] = i + trainNum
	}

	trainDF := loadDF.Subset(trainIdx)
	testDF := loadDF.Subset(testIdx)

	setMap := map[int]dataframe.DataFrame{
		0: trainDF,
		1: testDF,
	}

	for idx, setName := range []string{path + "training.csv", path + "tests.csv"} {
		filex, err := os.Create(setName)
		if err != nil {
			fmt.Println(err)
		}
		w := bufio.NewWriter(filex)
		if err := setMap[idx].WriteCSV(w); err != nil {
			fmt.Println(err)
		}
	}
}

func LogistcRegression(features *mat64.Dense, labels []float64, numSteps int, learningRate float64) []float64 {
	_, numWeights := features.Dims()
	weights := make([]float64, numWeights)
	s := rand.NewSource(time.Now().UnixNano())
	r := rand.New(s)
	for idx, _ := range weights {
		weights[idx] = r.Float64()
	}
	for i := 0; i < numSteps; i++ {
		var sumError float64
		for idx, label := range labels {
			featuresRow := mat64.Row(nil, idx, features)
			pred := logistc(featuresRow[0]*weights[0] + featuresRow[1]*weights[1])
			preError := label - pred
			sumError += math.Pow(preError, 2.0)
			for j := 0; j < len(featuresRow); j++ {
				weights[j] += learningRate * preError * pred * (1.0 - pred) * featuresRow[j]
			}
		}
	}
	return weights
}

func maintest() {
	path := ""
	file, err := os.Open(path + "training.csv")
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()
	reader := csv.NewReader(file)
	reader.FieldsPerRecord = 2
	rawcsvdata, err := reader.ReadAll()
	if err != nil {
		fmt.Println(err)
	}
	featuredata := make([]float64, 2*(len(rawcsvdata)-1))
	labels := make([]float64, len(rawcsvdata)-1)
	var featureidx int
	for idx, record := range rawcsvdata {
		if idx == 0 {
			continue
		}
		featureval, err := strconv.ParseFloat(record[0], 64)
		if err != nil {
			fmt.Println(err)
		}
		featuredata[featureidx] = featureval
		featuredata[featureidx+1] = 1.0
		featureidx += 2
		labelval, err := strconv.ParseFloat(record[1], 64)
		if err != nil {
			fmt.Println(err)
		}
		labels[idx-1] = labelval
	}

	features := mat64.NewDense(len(rawcsvdata)-1, 2, featuredata)
	weights := LogistcRegression(features, labels, 1000, 0.1)
	formula := "p=1/(1+exp(-m1*FICO.socre-m2))"
	fmt.Printf("\n%s\n\n m1=%f,m2=%f\n\n", formula, weights[0], weights[1])
}

func predict2(score float64) float64 {
	p := 1 / (1 + math.Exp(-13.417345*score+4.956825))
	if p >= 0.5 {
		return 1.0
	}
	return 0.0
}

func test() {
	path := ""
	file, err := os.Open(path + "test.csv")
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	reader := csv.NewReader(file)
	var observed []float64
	var predicted []float64
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
		obs, err := strconv.ParseFloat(record[1], 64)
		if err != nil {
			fmt.Println(err)
			continue
		}
		score, err := strconv.ParseFloat(record[0], 64)
		if err != nil {
			fmt.Println(err)
			continue
		}
		predictedval := predict2(score)
		observed = append(observed, obs)
		predicted = append(predicted, predictedval)
		line++
	}
	var truePosNeg int
	for idx, oVal := range observed {
		if oVal == predicted[idx] {
			truePosNeg++
		}
	}
	fmt.Println("正确率", float64(truePosNeg)/float64(len(observed)))
}
