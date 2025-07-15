package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
)

type DiskSearch struct {
	filepath string
	seg      jiebago.Segmenter
}

func NewDiskSearch(filepath string) *DiskSearch {
	mm := new(DiskSearch)
	mm.filepath = filepath
	mm.seg.LoadDictionary("dict.txt")
	return mm
}

func (mm *DiskSearch) GetQQQunByWord(word []string, filename string) []string {
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

		const N = 86907937
		file, _ := os.Open(mm.filepath)
		br := bufio.NewReader(file)
		i := 0
		for {
			line, _, err := br.ReadLine()
			if err == io.EOF {
				break
			}
			for j := 0; j < len(arr); j++ {
				if strings.Contains(string(line), arr[j]) {
					fmt.Println("come from ", string(line))
					fmt.Fprintln(save, string(line))
					resultstring = append(resultstring, string(line))
					break
				}
			}

			i++
			if i%10000 == 0 {
				fmt.Println(i)
			}
		}

		save.Flush()
		savefile.Close()
		//value := Upload(filelastpath)
	}
	return resultstring
}
