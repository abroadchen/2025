/*
Package 分布式存储

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package 分布式存储

import (
	"bufio"
	"fmt"
	"github.com/go-ego/riot"
	"go/types"
	"io"
	"os"
	"strconv"
)

type MEMriot struct {
	filepath string
	searcher *riot.Engine
}

func NewMEMriot(filepath string) *MEMriot {
	mr := new(MEMriot)
	mr.filepath = filepath
	mr.searcher = riot.New("zh")
	return mr
}

func (mr *MEMriot) LoadMEM() {
	const N = 86907937
	//var arrlist []string = make([]string, N, N)
	file, _ := os.Open(mr.filepath)
	br := bufio.NewReader(file)
	i := 0
	for {
		line, _, err := br.ReadLine()
		if err == io.EOF {
			break
		}
		//arrlist[i] = string(line)
		data := types.DocData{
			Content: string(line),
		}
		mr.searcher.Index(strconv.Itoa(i), data)
		i++
		if i%10000 == 0 {
			fmt.Println(i)
			mr.searcher.Flush()
		}
		if i == 50000 {
			return
		}
	}
	file.Close()
}

func (mr *MEMriot) Search(searchstr string) []string {
	req := types.SearchReq{
		Text: searchstr,
	}
	search := mr.searcher.Search(req)
	data := []string{}
	for i := 0; i < search.NumDocs; i++ {
		data = append(data, search.Docs.(types.ScoredDocs)[i].Content)
	}
	return data
}

func main() {
	path := ``
	mr := NewMEMriot(path)
	mr.LoadMEM()

	for {
		var data string
		fmt.Scanln(&data)
		arr := mr.Search(data)
		fmt.Println(arr)
		for i := 0; i < len(arr); i++ {
			fmt.Println(arr[i])
		}
	}
}
