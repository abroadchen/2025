package main

import (
	"bytes"
	"fmt"
	"net"
	"os"
	"runtime"
	"strconv"
)

func RecvFile(conn net.Conn) {

	var (
		res          string
		tempFilename string
		data         = make([]byte, 1024*1024)
		buf          []byte
		databuf      = bytes.NewBuffer(buf)
		filepos      int
	)
	defer conn.Close()
	fmt.Println("conn connected", conn.RemoteAddr())

	j := 0
	for {
		length, err := conn.Read(data)
		if err != nil {
			da := databuf.Bytes()
			fmt.Println("client %vhas disconnected%2d, %d", conn.RemoteAddr(), filepos, len(da))
			return
		}
		if 0 == j {
			res = string(data[:8])
			if "fileover" == res {
				xienum := int(data[8])
				mergeFileName := string(data[8:length])
				go MainMergeFile(xienum, mergeFileName)
				res = "file receiving finished" + mergeFileName
				conn.Write([]byte(res))
				fmt.Println(mergeFileName, "file receive succeed")
				return
			} else {
				filepos = int(data[0])
				tempFilename = string(data[1:length]) + strconv.Itoa(filepos)
				fmt.Println("create tempfile", tempFilename)
				fout, err := os.Create(tempFilename)
				if err != nil {
					fmt.Println("create tempfile failed", err)
					return
				}
				fout.Close()
			}
		} else {
			WriteTempFile(tempFilename, data[:length])
		}
		res = strconv.Itoa(filepos) + "receiving finished"
		conn.Write([]byte(res))
		j++
	}
}

func WriteTempFile(filename string, data []byte) {
	tempFile, err := os.OpenFile(filename, os.O_APPEND|os.O_RDWR, 0666)
	if err != nil {
		fmt.Println("open file failed", err)
		return
	}
	defer tempFile.Close()
	tempFile.Write(data)
}

func MainMergeFile(connnum int, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("create file failed", err)
		return
	}
	defer file.Close()
	for i := 0; i < connnum; i++ {
		MergeFile(filename+strconv.Itoa(i), file)
	}
	for i := 0; i < connnum; i++ {
		os.Remove(filename + strconv.Itoa(i))
	}
}

func MergeFile(rfilename string, wfile *os.File) {
	rfile, err := os.OpenFile(rfilename, os.O_RDWR, 0666)
	if err != nil {
		fmt.Println("open file failed", err)
		return
	}
	defer rfile.Close()
	stat, err := rfile.Stat()
	if err != nil {
		fmt.Println("stat file failed", err)
		return
	}
	num := stat.Size()
	buf := make([]byte, 1024*1024)
	for i := 0; int64(i) < num; {
		length, err := rfile.Read(buf)
		if err != nil {
			fmt.Println("read file failed", err)
			return
		}
		i += length
		wfile.Write(buf[:length])
	}
}

func main() {

	runtime.GOMAXPROCS(runtime.NumCPU())
	var (
		host   = ""
		port   = ""
		remote = host + ":" + port
	)
	fmt.Println("server on")

	listener, err := net.Listen("tcp", remote)
	if err != nil {
		fmt.Println("net.Listen err:", err)
		return
	}
	defer listener.Close()

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("listener.Accept err:", err)
			return
		}
		go RecvFile(conn)
	}

	//buf := make([]byte, 4096)
	//n, err := conn.Read(buf)
	//if err != nil {
	//	fmt.Println("conn.Read err:", err)
	//	return
	//}
	//fileName := string(buf[:n])
	//conn.Write([]byte("ok"))
	//
	//recvFile(conn, fileName)
}
