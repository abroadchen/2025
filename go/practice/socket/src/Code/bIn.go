package main

import (
	"bytes"
	"fmt"
	"golang.org/x/text/encoding/japanese"
	"golang.org/x/text/encoding/simplifiedchinese"
	"io"
	"os"
)

func convertToShiftJIS() {
	src := bytes.NewBuffer([]byte{0xe3, 0x82, 0xa2, 0xe3, 0x82, 0xbf, 0xe3, 0x83, 0xaa})
	e := japanese.ShiftJIS.NewEncoder()
	dst := new(bytes.Buffer)
	_, err := io.Copy(e.Writer(dst), src)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	for _, b := range dst.Bytes() {
		fmt.Printf("0x%2x", b)
	}
	fmt.Println()
}

func convertFromGB2313UTF8() {
	src := bytes.NewBuffer([]byte{0xd6, 0xd0, 0xb9, 0xfa})
	e := simplifiedchinese.GBK.NewDecoder()
	_, err := io.Copy(os.Stdout, e.Reader(src))
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
