package main

import (
	"fmt"
	"math/rand"
	"os"
	"path/filepath"
	"time"
)

const (
	line int = 1000
)

func main() {
	curDir, err := filepath.Abs(filepath.Dir(os.Args[0]))
	if err != nil {
		fmt.Printf("%v\n", err)
		return
	}
	fileDir := curDir + "/file-strore/"
	filename := "big_input_file.txt"
	inputFile, err := os.Create(fileDir + filename)
	if err != nil {
		fmt.Printf("%v\n", err)
	}
	defer inputFile.Close()

	s := rand.NewSource(time.Now().UnixNano())
	r := rand.New(s)
	for i := 0; i < line; i++ {
		words := r.Intn(10)
		var l string
		for j := 0; j < words; j++ {
			letters := 0
			for letters < 3 {
				letters = r.Intn(10)
			}
			var word string
			for k := 0; k < letters; k++ {
				ch := r.Intn(26)
				word += string(ch + 97)
			}
			l += word + " "
		}
		inputFile.WriteString(l + "\n")
	}
}
