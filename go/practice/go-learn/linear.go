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
	"github.com/go-gota/gota/dataframe"
	"github.com/sajari/regression"
	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
	"math"
	"os"
	"strconv"
)

func main1() {
	path := ""
	adfile, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer adfile.Close()

	adDF := dataframe.ReadCSV(adfile)
	fmt.Println(adDF.Describe())

	yvals := adDF.Col("Sales").Float()

	//pts := make(plotter.XYs, adDF.Nrow())
	//ptsPred := make(plotter.XYs, adDF.Nrow())
	//
	//for i, floatval := range adDF.Col("Radio").Float() {
	//	pts[i].X = floatval
	//	pts[i].Y = yvals[i]
	//	ptsPred[i].X = floatval
	//	ptsPred[i].Y = Predict(floatval)
	//}
	//p := plot.New()
	//if err != nil {
	//	fmt.Println(err)
	//}
	//p.X.Label.Text = "Radio"
	//p.Y.Label.Text = "Sales"
	//p.Add(plotter.NewGrid())
	//s, err := plotter.NewScatter(pts)
	//if err != nil {
	//	fmt.Println(err)
	//}
	//s.GlyphStyle.Radius = vg.Points(3)
	//l, err := plotter.NewLine(ptsPred)
	//if err != nil {
	//	fmt.Println(err)
	//}
	//l.LineStyle.Width = vg.Points(1)
	//l.LineStyle.Dashes = []vg.Length{vg.Points(5), vg.Points(5)}
	//p.Add(s, l)
	//if err := p.Save(4*vg.Inch, 4*vg.Inch, "last.png"); err != nil {
	//	fmt.Println(err)
	//}

	for _, colName := range adDF.Names() {
		//plotvals := make(plotter.Values, adDF.Nrow())
		plotvals := make(plotter.XYs, adDF.Nrow())
		for i, floatval := range adDF.Col(colName).Float() {
			//plotvals[i] = floatval
			plotvals[i].X = floatval
			plotvals[i].Y = yvals[i]
		}

		p := plot.New()
		if err != nil {
			fmt.Println(err)
		}

		p.X.Label.Text = colName
		p.Y.Label.Text = "y"
		p.Add(plotter.NewGrid())
		s, err := plotter.NewScatter(plotvals)

		//p.Title.Text = fmt.Sprintf("linear - %s", colName)
		//h, err := plotter.NewHist(plotvals, 16)
		if err != nil {
			fmt.Println(err)
		}

		s.GlyphStyle.Radius = vg.Points(1.0)
		p.Add(s)
		//h.Normalize(1)
		//p.Add(h)
		if err := p.Save(4*vg.Inch, 4*vg.Inch, colName+"_scatter.png"); err != nil {
			fmt.Println(err)
		}
	}

}

func Predict(Radio float64) float64 {
	return 9.32 + Radio*0.19
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
	if err != nil {
		fmt.Println(err)
	}
	var r regression.Regression
	r.SetObserved("Sales")
	r.SetVar(0, "TV")
	r.SetVar(1, "Radio")
	for i, record := range traindata {
		if i == 0 {
			continue
		}
		yval, err := strconv.ParseFloat(record[3], 64)
		if err != nil {
			fmt.Println(err)
		}
		TVval, err := strconv.ParseFloat(record[0], 64)
		if err != nil {
			fmt.Println(err)
		}
		Rval, err := strconv.ParseFloat(record[1], 64)
		if err != nil {
			fmt.Println(err)
		}
		r.Train(regression.DataPoint(yval, []float64{TVval, Rval}))
	}
	r.Run()
	fmt.Println(r.Formula)

	patht := ""
	ftest, err := os.Open(patht)
	if err != nil {
		fmt.Println(err)
	}
	defer ftest.Close()

	reader = csv.NewReader(ftest)
	reader.FieldsPerRecord = 4
	testdata, err := reader.ReadAll()
	if err != nil {
		fmt.Println(err)
	}

	var mAE float64
	for i, record := range testdata {
		if i == 0 {
			continue
		}
		yval, err := strconv.ParseFloat(record[3], 64)
		if err != nil {
			fmt.Println(err)
		}
		TVval, err := strconv.ParseFloat(record[0], 64)
		if err != nil {
			fmt.Println(err)
		}

		ypredicted, err := r.Predict([]float64{TVval})
		mAE += math.Abs(yval-ypredicted) / float64(len(testdata))
	}
	fmt.Println(mAE)
}
