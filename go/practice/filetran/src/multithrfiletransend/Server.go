package main

import (
	"bytes"
	"fmt"
	"net"
	"os"
	"runtime"
	"strconv"
	"time"
)

func SendMergeCommand(remote, mergeFileName string, coroutine int) {
	conn, err := net.Dial("tcp", remote)
	defer conn.Close()
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println("Sending merge command")
	var by [1]byte
	by[0] = byte(coroutine)
	var bys []byte
	databuf := bytes.NewBuffer(bys)
	databuf.WriteString("fileover")
	databuf.Write(bys[:])
	databuf.WriteString(mergeFileName)
	cmm := databuf.Bytes()
	in, err := conn.Write(cmm)
	if err != nil {
		fmt.Println(err, in)
		return
	}
	var msg = make([]byte, 1024)
	length, err := conn.Read(msg)
	if err != nil {
		fmt.Println(err)
		return
	}
	str := string(msg[:length])
	fmt.Println("trans finished", str)
}

func splitFile(remote string, c chan string, coroutineNum int, size int, fileName, MergeFileName string, begin, end int64) {
	conn, err := net.Dial("tcp", remote)
	defer conn.Close()
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println("file Sending")
	var by [1]byte
	by[0] = byte(coroutineNum)
	var bys []byte
	databuf := bytes.NewBuffer(bys)
	databuf.Write(by[:])
	databuf.WriteString(MergeFileName)
	bb := databuf.Bytes()
	in, err := conn.Write(bb)
	if err != nil {
		fmt.Println(err, in)
		return
	}
	var msg = make([]byte, 1024)
	length, err := conn.Read(msg)
	if err != nil {
		fmt.Println(err, length)
		return
	}
	file, err := os.OpenFile(fileName, os.O_RDWR, 0666)
	defer file.Close()
	if err != nil {
		fmt.Println(err, fileName)
		return
	}
	file.Seek(begin, 0)
	buf := make([]byte, size)
	var SendDataToNum int = 0
	for i := begin; int64(i) < end; i += int64(size) {
		length, err := file.Read(buf)
		if err != nil {
			fmt.Println(err)
			return
		}
		if length == size {
			if int64(i)+int64(size) >= end {
				SendDataNum, err := conn.Write(buf[:size-int(int64(i)+int64(size)-end)])
				if err != nil {
					fmt.Println(err)
					return
				}
				SendDataToNum += SendDataNum
			} else {
				SendDataNum, err := conn.Write(buf)
				if err != nil {
					fmt.Println(err)
					return
				}
				SendDataToNum += SendDataNum
			}
		} else {
			SendDataNum, err := conn.Write(buf[:length])
			if err != nil {
				fmt.Println(err)
				return
			}
			SendDataToNum += SendDataNum
		}
		lengths, err := conn.Read(msg)
		if err != nil {
			fmt.Println(err, lengths)
			return
		}
		fmt.Println("server info", string(msg[:lengths]))
	}
	fmt.Println(coroutineNum, "send data", SendDataToNum)
	c <- strconv.Itoa(coroutineNum) + "coroutine quit"
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	var (
		host          = ""
		port          = ""
		remote        = host + ":" + port
		fileName      = ""
		MergeFileName = ""
		coroutine     = 10
		bufsize       = 1024
	)
	fi, err := os.OpenFile(fileName, os.O_RDWR, 0666)
	if err != nil {
		fmt.Println("open file err:", err)
		return
	}
	stat, err := fi.Stat()
	if err != nil {
		fmt.Println("stat file err:", err)
		return
	}

	var size = stat.Size()
	fi.Close()

	eachsize := size / int64(coroutine)
	fmt.Println("Size:%d %d\n", size, eachsize)
	begintime := time.Now().Unix()

	c := make(chan string)
	var begin int64 = 0
	for i := 0; i < coroutine; i++ {
		if i == coroutine-1 {
			go splitFile(remote, c, i, bufsize, fileName, MergeFileName, begin, size)
			fmt.Println(begin, size, bufsize)
		} else {
			go splitFile(remote, c, i, bufsize, fileName, MergeFileName, begin, begin+eachsize)
			fmt.Println(begin, size, bufsize)
		}
		begin += eachsize
	}

	for j := 0; j < coroutine; j++ {
		fmt.Println(<-c)
	}

	midtime := time.Now().Unix()
	sendtime := midtime - begintime
	fmt.Println("send cost%dmin%dsec\n", sendtime/60, sendtime%60)

	SendMergeCommand(remote, MergeFileName, coroutine)

	endtime := time.Now().Unix()
	mergetime := endtime - midtime
	fmt.Println("merget cost%dmin%dsec\n", mergetime/60, mergetime%60)
	tot := endtime - begintime
	fmt.Println("total cost%dmin%dsec\n", tot/60, tot%60)
}
