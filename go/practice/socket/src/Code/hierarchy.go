package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"math"
)

func main() {
	fmt.Println("int64")
	ints := []int64{-2048, -1048, -512, -256, -128, -1, 0, 1, 128, 256, 512, 1024, 2048}
	for _, i := range ints {
		var b bytes.Buffer
		binary.Write(&b, binary.LittleEndian, i)
		bs := b.Bytes()
		fmt.Printf("%6d | %s | %s\n", i, hex(bs), bits(bs))
	}
	fmt.Println()
	fmt.Println("float64")
	floats := []float64{math.NaN(), math.Inf(-1), -128, -2.5, 2, -1, -0.5, 0, 0.5, 1, 2, 2.5, 128, math.Inf(1)}
	for _, i := range floats {
		var b bytes.Buffer
		binary.Write(&b, binary.LittleEndian, i)
		bs := b.Bytes()
		fmt.Printf("%7.2d | %s | %s\n", i, hex(bs), bits(bs))
	}

}
