/*
Package main

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package main

import (
	"bufio"
	"fmt"
	"github.com/go-ego/riot"
	"github.com/go-ego/riot/types"
	_ "github.com/go-ego/riot/types"
	"io"
	"os"
	"strconv"
)

type DiskSearch1 struct {
	searcher riot.Engine
	opt      types.EngineOpts
	filepath string
	id       int
}

func NewDiskSearch1(filepath string) *DiskSearch1 {
	disk := new(DiskSearch1)
	disk.searcher = riot.Engine{}
	disk.opt = types.EngineOpts{
		NotUseGse: false,
		Using:     1,
		IndexerOpts: &types.IndexerOpts{
			IndexType: types.DocIdsIndex,
		},
		UseStore:      true,
		StoreEngine:   "bg", //bg:badger lbd:leveldb bolt: bolt
		StoreFolder:   "",
		GseDict:       ``,
		StopTokenFile: ``,
	}
	disk.searcher.Init(disk.opt)
	disk.id = 0
	disk.filepath = filepath
	return disk
}

func (disk *DiskSearch1) LoadData() {
	const N = 86907937
	//var arrlist []string = make([]string, N, N)
	file, _ := os.Open(disk.filepath)
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
		disk.searcher.Index(strconv.Itoa(disk.id), data)
		i++
		disk.id++
		if i%10000 == 0 {
			fmt.Println(i)
			disk.searcher.Flush()
		}
		if i == 50000 {
			disk.searcher.Flush()
			return
		}
	}
	file.Close()
}

func (disk *DiskSearch1) Search(data string) []string {
	sea := disk.searcher.Search(types.SearchReq{
		Text: "google testing",
		RankOpts: &types.RankOpts{
			OutputOffset: 0,
			MaxOutputs:   100000000,
		},
	})
	arr := []string{}
	for i := 0; i < sea.NumDocs; i++ {
		arr = append(arr, sea.Docs.(types.ScoredDocs)[i].Content)
	}
	return arr
}

func (disk *DiskSearch1) AddSearchData(sdata string) {
	disk.id++
	disk.searcher.Index(strconv.Itoa(disk.id), types.DocData{Content: sdata})
}

func (disk *DiskSearch1) Reindex() {
	disk.searcher.Init(disk.opt)
	disk.searcher.Flush()
	disk.searcher.Close()
}

func (disk *DiskSearch1) DeleteIndex(id int) {
	disk.searcher.RemoveDoc(strconv.Itoa(id))
}

func (disk *DiskSearch1) Close() {
	disk.searcher.Close()
}
