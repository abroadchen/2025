package memmerge

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func LoadMEM(path string) []QQ {
	N := GetLineNumbers(path)
	alldata := make([]QQ, N, N)
	fi, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer fi.Close()
	br := bufio.NewReader(fi)
	i := 0
	for {
		line, _, err := br.ReadLine()
		if err == io.EOF {
			break
		}
		linestr := string(line)
		lines := strings.Split(linestr, "#")
		if len(lines) == 2 {
			numbers, isok := strconv.Atoi(lines[1])
			if isok != nil {
				fmt.Println(isok)
			}
			alldata[i] = QQ{numbers, lines[0]}
		} else {
			fmt.Println(linestr, "failed")
		}
		i++
	}
	return alldata
}

func MergeFileMEM(path1, path2, mergepath string) {
	arr1 := LoadMEM(path1)
	arr2 := LoadMEM(path2)
	savefile, _ := os.Create(mergepath)
	defer savefile.Close()
	save := bufio.NewWriter(savefile)
	i, j := 0, 0
	for i < len(arr1) && j < len(arr2) {
		if arr1[i].QQtimes < arr2[j].QQtimes {
			fmt.Fprintln(savefile, arr1[i].password+"#"+strconv.Itoa(arr1[i].QQtimes))
			i++
		} else if arr2[j].QQtimes < arr1[i].QQtimes {
			fmt.Fprintln(savefile, arr2[j].password+"#"+strconv.Itoa(arr2[j].QQtimes))
			j++
		} else {
			fmt.Fprintln(savefile, arr1[i].password+"#"+strconv.Itoa(arr1[i].QQtimes))
			fmt.Fprintln(savefile, arr2[j].password+"#"+strconv.Itoa(arr2[j].QQtimes))
			i++
			j++
		}
	}
	for i < len(arr1) {
		fmt.Fprintln(savefile, arr1[i].password+"#"+strconv.Itoa(arr1[i].QQtimes))
		i++
	}
	for j < len(arr2) {
		fmt.Fprintln(savefile, arr2[j].password+"#"+strconv.Itoa(arr2[j].QQtimes))
		j++
	}
	save.Flush()
}
