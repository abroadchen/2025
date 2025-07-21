/*
Package 分布式存储

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package distribute_store

import (
	"fmt"
	"github.com/go-ego/riot/types"
	"log"
)

var (
	searcher = roit.New("zh")
	text     = ""
	text1    = ""
	text2    = ""

	opts = types.EngineOpts{
		NotUseGse: false,
		Using:     1,
		IndexerOpts: &types.IndexerOpts{
			IndexType: types.DocIdsIndex,
		},
		UseStroe:      true,
		StoreEngine:   "bg", //bg:badger lbd:leveldb bolt: bolt
		StoreFolder:   "",
		GseDict:       ``,
		StopTokenFile: ``,
	}
)

func restoreIndex() {
	searcher.Init(opts)
	defer searcher.Close()
	searcher.Flush()
	log.Println("recover index no:", searcher.NumDocsIndexed())
}

func initEngine() {
	searcher.Init(opts)
	defer searcher.Close()

	searcher.Index("1", types.DocData{Content: text})
	searcher.Index("2", types.DocData{Content: text1})
	searcher.Index("3", types.DocData{Content: text2})

	searcher.RemoveDoc("3")

	searcher.Flush()

	log.Println("Created index no:", searcher.NumDocsIndexed())
}

func main() {
	initEngine()

	sea := searcher.Search(types.SearchReq{
		Text: "google testing",
		RankOpts: &types.RankOpts{
			OutputOffset: 0,
			MaxOutputs:   1000,
		},
	})

	fmt.Println("search resp:", sea, ":docs=", sea.Docs)
	fmt.Println(sea.Docs.(types.ScoredDocs)[0].Content)
}
