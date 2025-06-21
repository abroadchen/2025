package master

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func reducer(nr int, fileDir string) {
	mp := make(map[string]int)
	for {
		val, ok := <-ReduceChanIn
		if !ok {
			break
		}
		fmt.Println("reduce call", nr)
		file, err := os.Open(val)
		if err != nil {
			errMsg := fmt.Sprintf("reducer open file %s error", val)
			fmt.Println(errMsg)
			continue
		}
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			str := scanner.Text()
			arr := strings.Split(str, " ")
			if len(arr) != 2 {
				errMsg := fmt.Sprintf("reducer length file %s%s error %d", val, str, len(arr))
				fmt.Println(errMsg)
				continue
			}
			v, err := strconv.Atoi(arr[1])
			if err != nil {
				errMsg := fmt.Sprintf("reducer parse file %s error %s", val, str)
				fmt.Println(errMsg)
				continue
			}
			mp[arr[0]] += v
		}
		if err := scanner.Err(); err != nil {
			fmt.Println("reducer scan file error", err)
		}
		file.Close()
	}
	//outputFileName := path.Join(fileDir, "reduce-output-"+strconv.Itoa(nr))
	fileDir = ""
	outputFileName := fileDir + "/reduce-output-" + strconv.Itoa(nr)
	outputFileHandler, err := os.Create(outputFileName)
	if err != nil {
		errMsg := fmt.Sprintf("reducer create file %s error %d", outputFileName, nr)
		fmt.Println(errMsg)
	} else {
		for key, val := range mp {
			str := fmt.Sprintf("%s %d\n", key, val)
			outputFileHandler.WriteString(str)
		}
		outputFileHandler.Close()
	}
	ReduceChanOut <- outputFileName
}
