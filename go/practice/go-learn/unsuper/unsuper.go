/*
Package go_learn

	@author: June
	@since: 2025/7/21
	@desc:
*/
package unsuper

import (
	"fmt"
	"github.com/go-gota/gota/dataframe"
	"github.com/gonum/floats"
	"os"
)

type Centroid []float64

/*
main

	@Description: 聚类
*/
func main() {
	path := ""
	irisfile, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer irisfile.Close()
	irisDF := dataframe.ReadCSV(irisfile)
	speciesName := []string{
		"Iris-setosa",
		"Iris-versicolor",
		"Iris-virginica",
	}
	centroid := make(map[string]Centroid)
	cluster := make(map[string]dataframe.DataFrame)
	for _, species := range speciesName {
		filter := dataframe.F{
			Colname:    "species",
			Comparator: "==",
			Comparando: species,
		}
		filtered := irisDF.Filter(filter)
		cluster[species] = filtered
		summaryDF := filtered.Describe()
		var c Centroid
		for _, feature := range summaryDF.Names() {
			if feature == "column" || feature == "species" {
				continue
			}
			c = append(c, summaryDF.Col(feature).Float()[0])
		}
		centroid[species] = c
	}
	//for _, species := range speciesName {
	//	fmt.Println(species, centroid[species])
	//}
	labels := irisDF.Col("species").Records()
	floatCol := []string{
		"sepal_length", "sepal_width", "petal_length", "petal_width",
	}

	var silhoutette float64
	for idx, label := range labels {
		var a float64
		for i := 0; i < cluster[label].Nrow(); i++ {
			cur := dfFloatRow(irisDF, floatCol, idx)
			other := dfFloatRow(cluster[label], floatCol, i)
			a += floats.Distance(cur, other, 2) / float64(cluster[label].Nrow())
		}
		var otherCluster string
		var disToCluster float64
		for _, species := range speciesName {
			if species == label {
				continue
			}
			disTothisCluster := floats.Distance(centroid[label], centroid[species], 2)
			if disTothisCluster == 0 || disTothisCluster < disToCluster {
				otherCluster = species
				disToCluster = disTothisCluster
			}
		}
		var b float64
		for i := 0; i < cluster[otherCluster].Nrow(); i++ {
			cur := dfFloatRow(irisDF, floatCol, idx)
			other := dfFloatRow(cluster[otherCluster], floatCol, i)
			b += floats.Distance(cur, other, 2) / float64(cluster[otherCluster].Nrow())
		}
		if a > b {
			silhoutette += ((b - a) / a) / float64(len(labels))
		}
		silhoutette /= float64(cluster[otherCluster].Nrow())
	}
	fmt.Println(silhoutette)

}

func dfFloatRow(df dataframe.DataFrame, names []string, idx int) []float64 {
	var row []float64
	for _, name := range names {
		row = append(row, df.Col(name).Float()[idx])
	}
	return row
}
