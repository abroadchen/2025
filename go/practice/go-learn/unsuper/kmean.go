/*
Package unsuper

	@author: June
	@since: 2025/7/21
	@desc:
*/
package unsuper

import (
	""
	"encoding/csv"
	"fmt"
	"github.com/mash/gokmeans"
	"io"
	"os"
	"strconv"
)

func main() {
	path := ""
	file, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	r := csv.NewReader(file)
	r.FieldsPerRecord = 3

	var data []gokmeans.Node
	for {
		record, err := r.Read()
		if err == io.EOF {
			break
		}
		if err != nil {
			fmt.Println(err)
		}

		if record[0] == "Driver_ID" {
			continue
		}
		var point []float64
		for i := 1; i < 3; i++ {
			val, err := strconv.ParseFloat(record[i], 64)
			if err != nil {
				fmt.Println(err)
			}
			point = append(point, val)
		}
		data = append(data, gokmeans.Node{point[0], point[1]})
	}
	succ, centroids := gokmeans.Train(data, 2, 50)
	if !succ {
		fmt.Println("failed to train")
	}
	for _, centroid := range centroids {
		fmt.Println(centroid)
		for _, observation := range data {
			idx := gokmeans.Nearest(observation, centroids)
			fmt.Println(observation, "belongs to ", idx+1, ".")
		}
	}
}
