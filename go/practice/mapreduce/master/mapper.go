package master

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

type MapInput struct {
	FileName string
	Nr       int
}

func mapper(nr int, fileDir string) {
	for {
		val, ok := <-MapChanIn
		if !ok {
			break
		}
		inputFileName := val.FileName
		nr := val.Nr
		file, err := os.Open(inputFileName)
		if err != nil {
			errMsg := fmt.Sprintf("Error opening input file %s for reading %d", inputFileName, nr)
			fmt.Println(errMsg)
			MapChanOut <- ""
			continue
		}
		mp := make(map[string]int)
		scanner := bufio.NewScanner(file)
		scanner.Split(bufio.ScanWords)
		for scanner.Scan() {
			str := scanner.Text()
			mp[str]++
		}
		file.Close()
		fileDir = ""
		//outputfileName := path.Join(fileDir, "mapper-output-"+strconv.Itoa(nr))
		outputfileName := fileDir + "/mapper-output-" + strconv.Itoa(nr)
		outputfileHandler, err := os.Create(outputfileName)
		if err != nil {
			errMsg := fmt.Sprintf("Error creating output file %s for writing %d", outputfileName, nr)
			fmt.Println(errMsg)
		} else {
			for key, val := range mp {
				str := fmt.Sprintf("%s %d\n", key, val)
				outputfileHandler.WriteString(str)
			}
			outputfileHandler.Close()
		}
		MapChanOut <- outputfileName
	}
}
