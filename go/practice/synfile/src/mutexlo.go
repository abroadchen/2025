package main

import (
	"bufio"
	"fmt"
	"github.com/axgle/mahonia"
	"io"
	"os"
	"strings"
	"sync"
)

const N1 = 20151574
const M1 = 13180805

type toFile struct {
	myfile *os.File
	fmutex *sync.RWMutex
	save   *bufio.Writer
}

func NewtoFile(path string) *toFile {
	f, err := os.Create(path)
	if err != nil {
		return nil
	}
	fmutex := new(sync.RWMutex)
	save := bufio.NewWriter(f)
	myto := new(toFile)
	myto.fmutex = fmutex
	myto.myfile = f
	myto.save = save
	return myto
}

func evgSplit(num, N int) []int {
	arr := []int{}
	if num%N == 0 {
		for i := 0; i < N; i++ {
			arr = append(arr, num/N)
		}
	} else {
		evg := (num - num%N) / (N - 1)
		for i := 0; i < N-1; i++ {
			arr = append(arr, evg)
			num -= evg
		}
		arr = append(arr, num)
	}
	return arr
}

func FanINALL(chall []chan string, chc chan<- string) {
	var n string
	for {
		select {
		case n = <-chall[0]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[1]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[2]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[3]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[4]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[5]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[6]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[7]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[8]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[9]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		case n = <-chall[10]:
			if n == "" {
				close(chc)
				return
			}
			chc <- n
		}
	}
	fmt.Println("func FanIN()")
}

func FanINN(ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10 <-chan string, chc chan<- string) {
	var n string
	isok1 := false
	isok2 := false
	isok3 := false
	isok4 := false
	isok5 := false
	isok6 := false
	isok7 := false
	isok8 := false
	isok9 := false
	isok10 := false
	for {
		select {
		case n = <-ch1:
			if n == "" {
				isok1 = true
				break
			}
			chc <- n
		case n = <-ch2:
			if n == "" {
				isok2 = true
				break
			}
			chc <- n
		case n = <-ch3:
			if n == "" {
				isok3 = true
				break
			}
			chc <- n
		case n = <-ch4:
			if n == "" {
				isok4 = true
				break
			}
			chc <- n
		case n = <-ch5:
			if n == "" {
				isok5 = true
				break
			}
			chc <- n
		case n = <-ch6:
			if n == "" {
				isok6 = true
				break
			}
			chc <- n
		case n = <-ch7:
			if n == "" {
				isok7 = true
				break
			}
			chc <- n
		case n = <-ch8:
			if n == "" {
				isok8 = true
				break
			}
			chc <- n
		case n = <-ch9:
			if n == "" {
				isok9 = true
				break
			}
			chc <- n
		case n = <-ch10:
			if n == "" {
				isok10 = true
				break
			}
			chc <- n
		}
		if isok1 && isok2 && isok3 && isok4 && isok5 && isok6 && isok7 && isok8 && isok9 && isok10 {
			return
		}
	}
}

func FanOUTT(cha <-chan string, chd, chk chan<- string) {
	for n := range cha {
		if n[0] == '0' {
			chd <- n
		} else {
			chk <- n
		}
	}
}

func CconsumerX(ch <-chan string, path string) {
	savefile, _ := os.Create(path)
	save := bufio.NewWriter(savefile)
	for n := range ch {
		fmt.Println("<-", n)
		fmt.Fprintln(save, n)
	}
	save.Flush()
	savefile.Close()
}

func savefile(input string, ch chan string) {
	var path = ""
	savefile, _ := os.Create(path)
	save := bufio.NewWriter(savefile)
	for n := range ch {
		fmt.Println("<-", n)
		fmt.Fprintln(save, n)
	}
	save.Flush()
	savefile.Close()
}

func Search(mylist []string, start int, end int, findstr string, id int, wg *sync.WaitGroup, toFile *toFile) {
	result := []string{}
	for i := start; i < end; i++ {
		if strings.Contains(mylist[i], findstr) {
			//ch<-mylist[i]
			result = append(result, mylist[i])
		}
	}
	//close(ch)
	toFile.fmutex.Lock()
	for _, line := range result {
		fmt.Println(line)
		fmt.Fprintln(toFile.save, line)
	}
	toFile.fmutex.Unlock()
	wg.Done()
}

func LoadMEM(path string, N int) []string {
	fi, err := os.Open(path)
	if err != nil {
		fmt.Println("file read err", err)
		return nil
	}
	defer fi.Close()
	mystrs := make([]string, N, N)
	br := bufio.NewReader(fi)
	i := 0
	for {
		line, _, err := br.ReadLine()
		if err == io.EOF {
			break
		}
		enc := mahonia.NewDecoder("gb2312")
		laststr := enc.ConvertString(string(line))
		mystrs[i] = laststr
		if i%1000000 == 0 {
			fmt.Println(i)
		}
		i++
	}
	return mystrs
}

func main() {
	mylist1 := LoadMEM("", M1)
	mylist2 := LoadMEM("", N1)
	arrlist1 := evgSplit(M1, 11)
	arrlist2 := evgSplit(N1, 11)
	quit := make(chan bool)
	for {
		var input string
		fmt.Scanln(&input)

		//ch := make([]chan string, 11, 11)
		//for i := 0; i < 11; i++ {
		//	ch[i] = make(chan string, 4096)
		//}
		//last := make(chan string, 4096)
		//go savefile(input, last)
		//FanINALL(ch, last)

		var path = ""
		myto := NewtoFile(path)

		var wg *sync.WaitGroup = new(sync.WaitGroup)
		var i = 0
		for i = 0; i < len(arrlist1)-1; i++ {
			wg.Add(1)
			go Search(mylist1, arrlist1[0]*i, arrlist1[0]*(i+1), input, i, wg, myto)
		}
		wg.Add(1)
		go Search(mylist1, arrlist1[i]*i, M1, input, i, wg, myto)
		var j = 0
		for j = 0; j < len(arrlist2)-1; j++ {
			wg.Add(1)
			go Search(mylist2, arrlist2[0]*j, arrlist2[0]*(j+1), input, j, wg, myto)
		}
		wg.Add(1)
		go Search(mylist2, arrlist2[j]*j, N1, input, i, wg, myto)
		wg.Wait()

		fmt.Println("data has ready")
		myto.save.Flush()
		myto.myfile.Close()
	}
	<-quit
}
