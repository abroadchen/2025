package main

import (
	"context"
	"fmt"
	"github.com/olivere/elastic/v7"
	"log"
	"os"
)

var client *elastic.Client
var host = "http://127.0.0.1:9200/"

func init() {
	errorlog := log.New(os.Stdout, "APP", log.LstdFlags)
	client, err := elastic.NewClient(elastic.SetURL(host), elastic.SetErrorLog(errorlog))
	if err != nil {
		panic(err)
	}
	info, code, err := client.Ping(host).Do(context.Background())
	if err != nil {
		panic(err)
	}
	fmt.Printf("Elasticsearch returned with code %d and version %s\n", code, info.Version.Number)
}

func main() {

}
