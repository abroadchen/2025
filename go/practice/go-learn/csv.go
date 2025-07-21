/*
Package go_learn

	@author: June
	@since: 2025/7/20
	@desc:
*/
package go_learn

import (
	"encoding/csv"
	"fmt"
	"io"
	"os"
)

func main() {
	path := "test.csv"
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer file.Close()
	reader := csv.NewReader(file)
	reader.FieldsPerRecord = -1
	csvData, err := reader.ReadAll()
	if err != nil {
		panic(err)
	}
	fmt.Println(csvData)
	for _, row := range csvData {
		fmt.Println(row)
	}
	//2
	var data [][]string
	for {
		record, err := reader.Read()
		if err == io.EOF {
			break
		}
		data = append(data, record)
	}
	for _, row := range data {
		fmt.Println(row)
	}

}
