package single

import (
	"os"
	"strconv"
	"strings"
)

func Worker(word string, fii *os.File, email string) {
	_, err := os.Stat(Cachepath + "/" + word)
	if err != nil {
		os.Mkdir(Cachepath+"/"+word, 0777)
		svpath := Cachepath + "/" + word + "/" + word + ".txt"
		_, err := os.Stat(svpath)
		total := 0
		if err != nil {
			mylist := FindQQbyString(word, svpath)
			for _, mystr := range mylist {
				mydatalist := strings.Split(mystr, "\t")
				qqnumstr := strings.Replace(mydatalist[1], "\"", "", -1)
				qqnum, _ := strconv.Atoi(qqnumstr)
				myqlist := bin_searchQQ(Qfindex, Qfi, qqnum)
				for _, qq := range myqlist {
					
				}

				nonumstr := strings.Replace(mydatalist[2], "\"", "", -1)
				nonum, err := strconv.Atoi(nonumstr)
				if err != nil {
					nonum = 0
				} else {
					total += nonum
				}
			}
		}
	}
}
