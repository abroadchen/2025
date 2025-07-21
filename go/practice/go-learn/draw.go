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
	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
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
	for _, colname := range irisDF.Names() {
		if colname != "species" {
			v := make(plotter.Values, irisDF.Nrow())
			for i, flotval := range irisDF.Col(colname).Float() {
				v[i] = flotval
			}
			p := plot.New()

			p.Title.Text = fmt.Sprintf("histogram of a %s", colname)
			h, err := plotter.NewHist(v, 16)
			if err != nil {
				fmt.Println(err)
			}
			h.Normalize(1)
			p.Add(h)
			if err = p.Save(4*vg.Inch, 4*vg.Inch, colname+"_hist.png"); err != nil {
				fmt.Println(err)
			}
		}
	}

	p := plot.New()
	p.Title.Text = "box plots"
	p.Y.Label.Text = "value"
	w := vg.Points(20)
	for idx, colname := range irisDF.Names() {
		if colname != "species" {
			v := make(plotter.Values, irisDF.Nrow())
			for i, flotval := range irisDF.Col(colname).Float() {
				v[i] = flotval
			}
			b, err := plotter.NewBoxPlot(w, float64(idx), v)
			if err != nil {
				fmt.Println(err)
			}
			p.Add(b)
		}
	}
	p.NominalY("sepal_length", "sepal_width", "sepal_height")
	if err = p.Save(4*vg.Inch, 4*vg.Inch, "xx.png"); err != nil {
		fmt.Println(err)
	}
}
