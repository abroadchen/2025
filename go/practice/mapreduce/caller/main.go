package main

import (
	"bufio"
	"fmt"
	"mapreduce/master"
	"os"
	"path/filepath"
	"strconv"
)

const (
	LIMIT int = 1000
)

func main() {
	curDir, err := filepath.Abs(filepath.Dir(os.Args[0]))
	if err != nil {
		fmt.Printf("%v\n", err)
		return
	}
	//fileDir := path.Join(curDir, "file-strore")
	fileDir := curDir + "/file-strore/"
	_ = os.Mkdir(fileDir, os.ModePerm)
	filename := "big_input_file.txt"
	fileDir += filename
	inputFile, err := os.Open(fileDir)
	if err != nil {
		fmt.Printf("%v\n", err)
	}
	defer inputFile.Close()
	filePieceArr := []string{}
	scanner := bufio.NewScanner(inputFile)
	piece := 1
outer:
	for {
		outputFileName := "input_piece_" + strconv.Itoa(piece)
		//outputFilePos := path.Join(fileDir, outputFileName)
		fileDir := ""
		outputFilePos := fileDir + "/" + outputFileName
		filePieceArr = append(filePieceArr, outputFilePos)
		outputFile, err := os.Create(outputFilePos)
		if err != nil {
			fmt.Printf("%v\n", err)
			continue
		}
		defer outputFile.Close()
		for cnt := 0; cnt < LIMIT; cnt++ {
			if !scanner.Scan() {
				break outer
			}
			_, err := outputFile.WriteString(scanner.Text() + "\n")
			if err != nil {
				fmt.Printf("%v\n", err)
				return
			}
		}
		piece++
	}
	res := master.Handle(filePieceArr, fileDir)
	fmt.Println(res)
}
