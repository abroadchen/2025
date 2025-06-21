package memmerge

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func MergeFileDisk(path1, path2, newpath string) {
	length1, length2 := GetLineNumbers(path1), GetLineNumbers(path2)
	fi1, _ := os.Open(path1)
	fi2, _ := os.Open(path2)
	defer fi1.Close()
	defer fi2.Close()
	br1 := bufio.NewReader(fi1)
	br2 := bufio.NewReader(fi2)
	savefile, _ := os.Create(newpath)
	defer savefile.Close()
	save := bufio.NewWriter(savefile)

	i, j := 0, 0
	line1, _, _ := br1.ReadLine()
	line2, _, _ := br2.ReadLine()
	linelist1 := strings.Split(string(line1), " # ")
	linelist2 := strings.Split(string(line2), " # ")
	var password1, password2 string
	var passtime1, passtime2 int
	if len(linelist1) == 2 {
		password1 = linelist1[0]
		passtime1, _ = strconv.Atoi(linelist1[1])
	}
	if len(linelist2) == 2 {
		password2 = linelist2[0]
		passtime2, _ = strconv.Atoi(linelist2[1])
	}

	for i < length1 && j < length2 {
		if passtime1 < passtime2 {
			fmt.Fprintf(savefile, password1+" # "+strconv.Itoa(passtime1))
			line1, _, _ = br1.ReadLine()
			linelist1 = strings.Split(string(line1), " # ")
			if len(linelist1) == 2 {
				password1 = linelist1[0]
				passtime1, _ = strconv.Atoi(linelist1[1])
			}
			i++
		} else if passtime1 > passtime2 {
			fmt.Fprintf(savefile, password2+" # "+strconv.Itoa(passtime2))
			line2, _, _ = br2.ReadLine()
			linelist2 = strings.Split(string(line2), " # ")
			if len(linelist2) == 2 {
				password2 = linelist2[0]
				passtime2, _ = strconv.Atoi(linelist2[1])
			}
			j++
		} else {
			fmt.Fprintf(savefile, password1+" # "+strconv.Itoa(passtime1))
			line1, _, _ = br1.ReadLine()
			linelist1 = strings.Split(string(line1), " # ")
			if len(linelist1) == 2 {
				password1 = linelist1[0]
				passtime1, _ = strconv.Atoi(linelist1[1])
			}
			i++
			fmt.Fprintf(savefile, password2+" # "+strconv.Itoa(passtime2))
			line2, _, _ = br2.ReadLine()
			linelist2 = strings.Split(string(line2), " # ")
			if len(linelist2) == 2 {
				password2 = linelist2[0]
				passtime2, _ = strconv.Atoi(linelist2[1])
			}
			j++
		}
	}
	for i < length1 {
		fmt.Fprintf(savefile, password1+" # "+strconv.Itoa(passtime1))
		line1, _, _ = br1.ReadLine()
		linelist1 = strings.Split(string(line1), " # ")
		if len(linelist1) == 2 {
			password1 = linelist1[0]
			passtime1, _ = strconv.Atoi(linelist1[1])
		}
		i++
	}
	for j < length2 {
		fmt.Fprintf(savefile, password2+" # "+strconv.Itoa(passtime2))
		line2, _, _ = br2.ReadLine()
		linelist2 = strings.Split(string(line2), " # ")
		if len(linelist2) == 2 {
			password2 = linelist2[0]
			passtime2, _ = strconv.Atoi(linelist2[1])
		}
		j++
	}
	save.Flush()
}
