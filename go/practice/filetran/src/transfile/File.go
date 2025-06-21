package main

import (
	"fmt"
	"os"
)

func main() {

	path := ""
	fileInfo, err := os.Stat(path)
	if err != nil {
		fmt.Println("os.Stat err", err)
		return
	}
	fmt.Println("filename", fileInfo.Name())
	fmt.Println("filesize", fileInfo.Size())

}
