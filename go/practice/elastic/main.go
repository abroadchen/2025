package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

func LoadfiletoMEM(filpath string) []string {
	const N = 86907937
	var arrlist []string = make([]string, N, N)
	filepath := ""
	file, _ := os.Open(filepath)
	br := bufio.NewReader(file)
	i := 1
	for {
		line, _, err := br.ReadLine()
		if err == io.EOF {
			break
		}
		arrlist[i] = string(line)

		//for j := 0; j < len(arr); j++ {
		//	if strings.Contains(string(line), arr[j]) {
		//		fmt.Println("come from ", string(line))
		//		fmt.Fprintln(save, string(line))
		//		res = append(res, string(line))
		//		break
		//	}
		//}

		i++
		if i%10000 == 0 {
			fmt.Println(i)
		}
	}
	file.Close()
	return arrlist
}
