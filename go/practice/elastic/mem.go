package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
)

type MEMSearch struct {
	filepath string
	memdata  []string
	seg      jiebago.Segmenter
}

func NewMEMSearch(filepath string) *MEMSearch {
	mm := new(MEMSearch)
	mm.filepath = filepath
	mm.memdata = LoadfiletoMEM(mm.filepath)
	mm.seg.LoadDictionary("dict.txt")
	return mm
}

func (mm *MEMSearch) GetQQQunByWord(word []string, filename string) []string {
	var allword string
	for i := 0; i < len(word); i++ {
		allword += word[i]
	}
	allword += filename

	filesavepath := ""
	filelastpath := filesavepath + allword + ".txt"
	_, err := os.Stat(filelastpath)
	resultstring := []string{}

	if err == nil {
		fmt.Println("file not exist")
		file, _ := os.Open(filelastpath)
		br := bufio.NewReader(file)
		for {
			line, _, err := br.ReadLine()
			if err == io.EOF {
				break
			}
			fmt.Println("来自缓存", string(line))
			resultstring = append(resultstring, string(line))
		}
	} else {
		fmt.Println("file not exist")
		savefile, _ := os.Create(filelastpath)
		save := bufio.NewWriter(savefile)

		var arr []string
		for i := 0; i < len(word); i++ {
			arrch := mm.seg.CutForSearch(word[i], true)
			arr = append(arr, word[i])
			arr = append(arr, returnstr(arrch)...)
		}

		for i := 0; i < len(mm.memdata); i++ {
			for j := 0; j < len(arr); j++ {
				if strings.Contains(mm.memdata[i], arr[j]) {
					fmt.Println("来自搜索", mm.memdata[i])

					fmt.Fprintln(save, mm.memdata[i])
					resultstring = append(resultstring, mm.memdata[i])
					break
				}
			}
		}
		save.Flush()
		savefile.Close()
	}
	return resultstring
}

func returnstr(ch <-chan string) []string {
	var strarr []string
	for word := range ch {
		fmt.Println(word)
		strarr = append(strarr, word)
	}
	return strarr
}
