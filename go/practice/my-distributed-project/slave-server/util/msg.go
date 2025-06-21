package util

import (
	"fmt"
	"net"
	"os/exec"
	"sort"
	"strconv"
	"time"
)

func MsgHandler(conn net.Conn) {
	buf := make([]byte, 16)
	defer conn.Close()
	arr := []int{}
	for {
		n, err := conn.Read(buf)
		if err != nil {
			fmt.Println("conn closed", conn.RemoteAddr())
			return
		}
		if n == 16 {
			data1 := BytesToInt(buf[:8])
			data2 := BytesToInt(buf[8:])
			fmt.Println("data1, data2", data1, data2)
			if data1 == 0 && data2 == 0 {
				arr = make([]int, 0, 0)
			}
			if data1 == 1 {
				arr = append(arr, data2)
			}
			if data1 == 0 && data2 == 1 {
				fmt.Println("data receive complated")
				sort.Ints(arr)
				SendArr(arr, conn)
				arr = make([]int, 0, 0)
			}
			if data1 == 3 {
				mybuf := make([]byte, data2)
				myn, _ := conn.Read(mybuf)
				if myn == data2 {
					cmd := exec.Command(string(mybuf))
					cmd.Run()
				}
			}
		}
	}
}

func SendArr(arr []int, conn net.Conn) {
	length := len(arr)
	myb := IntToBytes(0)
	myb = append(myb, IntToBytes(0)...)
	conn.Write(myb)
	for i := 0; i < length; i++ {
		mydata := IntToBytes(1)
		mydata = append(mydata, IntToBytes(arr[i])...)
		conn.Write(mydata)
	}
	myend := IntToBytes(0)
	myend = append(myb, IntToBytes(1)...)
	conn.Write(myend)
}

func SendCMD(cmd string, conn net.Conn) {
	length := len(cmd)
	myb := IntToBytes(3)
	myb = append(myb, IntToBytes(length)...)
	conn.Write(myb)
	conn.Write([]byte(cmd))
}

func Merge(in1, in2 <-chan int) <-chan int {
	out := make(chan int, 1024)
	go func() {
		v1, ok1 := <-in1
		v2, ok2 := <-in2
		for ok1 || ok2 {
			if !ok2 || (ok1 && v1 <= v2) {
				out <- v1
				v1, ok1 = <-in1
			} else {
				out <- v2
				v2, ok2 = <-in2
			}
		}
		close(out)
		fmt.Println("chan mergesort")
	}()
	return out
}

func ServerMsgHandlerX(conn net.Conn) <-chan int {
	out := make(chan int, 1024)
	buf := make([]byte, 16)
	defer conn.Close()
	arr := []int{}
	for {
		n, err := conn.Read(buf)
		if err != nil {
			fmt.Println("conn closed", conn.RemoteAddr())
			return nil
		}
		if n == 16 {
			data1 := BytesToInt(buf[:8])
			data2 := BytesToInt(buf[8:])
			fmt.Println("data1, data2", data1, data2)
			if data1 == 0 && data2 == 0 {
				arr = make([]int, 0, 0)
			}
			if data1 == 1 {
				arr = append(arr, data2)
			}
			if data1 == 0 && data2 == 1 {
				fmt.Println("data receive complated")
				for i := 0; i < len(arr); i++ {
					out <- arr[i]
				}
				close(out)
				SendCMD("calc", conn)
				arr = make([]int, 0, 0)
				return out
			}
		}
	}
	return nil
}

func main() {
	arrlist := [][]int{{1, 100, 2, 99}, {103, 109, 106, 102}}
	sortResult := []<-chan int{}
	//cmds := []string{"calc", "notepad"}
	for i := 1; i <= 2; i++ {
		tcpaddr, err := net.ResolveTCPAddr("tcp4", "127.0.0.1:8080"+strconv.Itoa(i))
		if err != nil {
			fmt.Println(err)
		}
		conn, err := net.DialTCP("tcp", nil, tcpaddr)
		if err != nil {
			fmt.Println(err)
		}
		SendArr(arrlist[i-1], conn)
		sortResult = append(sortResult, ServerMsgHandlerX(conn))
		//SendCMD(cmds[i-1], conn)
	}
	fmt.Println("-------------------------")
	last := Merge(sortResult[0], sortResult[1])
	for v := range last {
		fmt.Println("%d ", v)
	}
	time.Sleep(time.Second * 20)
}
