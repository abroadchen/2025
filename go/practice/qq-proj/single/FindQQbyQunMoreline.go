package single

import (
	"fmt"
	"os"
	"strings"
)

const N = 1449403409

func bin_searchQQ(findex, fii *os.File, QQqun int) []string {
	low := 0
	high := N - 1

	for low <= high {
		mid := (low + high) / 2
		findex.Seek(int64(mid*15), 0)
		bx := make([]byte, 15, 15)
		_, _ = findex.Read(bx)
		var data int64
		fmt.Sscanf(string(bx), "%15d", &data)

		fii.Seek(int64(data), 0)
		b := make([]byte, 50, 50)
		length, _ := fii.Read(b)
		var i int
		for i = 0; i < length-1; i++ {
			if b[i] == '\n' && i >= 5+3+3+3+6 {
				break
			}
		}
		midstr := string(b[:i])
		midlist := strings.Split(midstr, " # ")
		var midQQ int
		fmt.Sscanf(midlist[2], "%d", &midQQ)

		if midQQ > QQqun {
			high = mid - 1
		} else if midQQ < QQqun {
			low = mid + 1
		} else {
			mystrlist := make([]string, 0, 0)
			templist := strings.Split(midstr, " # ")
			mystrlist = append(mystrlist, templist[0])

			tmp_up := mid
			for {
				tmp_up -= 1
				if tmp_up < low {
					break
				}
				findex.Seek(int64(tmp_up*15), 0)
				bx := make([]byte, 15, 15)
				_, _ = findex.Read(bx)
				var data int64
				fmt.Sscanf(string(bx), "%15d", &data)

				fii.Seek(int64(data), 0)
				b := make([]byte, 50, 50)
				length, _ := fii.Read(b)
				var i int
				for i = 0; i < length-1; i++ {
					if b[i] == '\n' && i >= 5+3+3+3+6 {
						break
					}
				}
				upstr := string(b[:i])
				uplist := strings.Split(upstr, " # ")
				var upQQ int
				fmt.Sscanf(uplist[2], "%d", &upQQ)
				if upQQ == midQQ {
					templist := strings.Split(upstr, " # ")
					mystrlist = append(mystrlist, templist[0])
				} else {
					break
				}
			}

			tmp_down := mid
			for {
				tmp_down += 1
				if tmp_down > high {
					break
				}
				findex.Seek(int64(tmp_down*15), 0)
				bx := make([]byte, 15, 15)
				_, _ = findex.Read(bx)
				var data int64
				fmt.Sscanf(string(bx), "%15d", &data)

				fii.Seek(int64(data), 0)
				b := make([]byte, 50, 50)
				length, _ := fii.Read(b)
				var i int
				for i = 0; i < length-1; i++ {
					if b[i] == '\n' && i >= 5+3+3+3+6 {
						break
					}
				}
				downstr := string(b[:i])
				downlist := strings.Split(downstr, " # ")
				var downQQ int
				fmt.Sscanf(downlist[2], "%d", &downQQ)
				if downQQ == midQQ {
					templist := strings.Split(downstr, " # ")
					mystrlist = append(mystrlist, templist[0])
				} else {
					break
				}
			}
			return mystrlist
		}
	}
	return []string{}
}
