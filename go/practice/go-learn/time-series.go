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
	"image/color"
	"os"
)

func main() {
	path := ""
	file, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()
	passengerDF := dataframe.ReadCSV(file)
	yvals := passengerDF.Col("AirPassengers").Float()
	pts := make(plotter.XYs, passengerDF.Nrow())
	for i, floatval := range passengerDF.Col("time").Float() {
		pts[i].X = floatval
		pts[i].Y = yvals[i]
	}
	p := plot.New()
	p.X.Label.Text = "Time Series"
	p.Y.Label.Text = "passengers"
	p.Add(plotter.NewGrid())
	l, err := plotter.NewLine(pts)
	if err != nil {
		fmt.Println(err)
	}
	l.LineStyle.Width = vg.Points(1)
	l.LineStyle.Color = color.RGBA{R: 255, A: 255}
	p.Add(l)
	if err := p.Save(4*vg.Inch, 4*vg.Inch, "time.png"); err != nil {
		fmt.Println(err)
	}
}
