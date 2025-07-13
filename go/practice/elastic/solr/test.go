package solr

import (
	"fmt"
	"github.com/rtt/Go-Solr"
	"log"
)

func main() {
	s, err := solr.Init("localhost", 8983, "new_core")
	fmt.Printf("Init Server:%v\n", s, err)

	q := solr.Query{
		Params: solr.URLParamMap{
			"q":           []string{"*"},
			"facet.field": []string{"*"},
			"facet":       []string{"true"},
		},
		Rows: 10,
	}
	
	res, err := s.Select(&q)
	if err != nil {
		log.Printf("Query Server:%v\n", err)
	}
	fmt.Printf("Query Server:%v\n", res)

}
