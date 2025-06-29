package main

import (
	"context"
	"fmt"
	"github.com/olivere/elastic/v7"
	"log"
	"os"
	"reflect"
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

func get() {
	get1, err := client.Get().Index("软件").Type("QQqun").Id("2").Do(context.Background())
	if err != nil {
		panic(err)
	}
	if get1.Found {
		fmt.Println(get1.Id, get1.Index, get1.Version, get1.Type, get1)
	}
}

func delete() {
	res, err := client.Delete().Index("<UNK>").Type("QQqun").Id("2").Do(context.Background())
	if err != nil {
		panic(err)
	}
	fmt.Println(res.Result)
}

func update() {
	res, err := client.Update().Index("<UNK>").Type("QQqun").Id("2").Doc(map[string]interface{}{"": ""}).Do(context.Background())
}

func list(size, page int) {
	if size < 0 || page < 1 {
		return
	}
	res, err := client.Search("软件").Type("QQqun").Size(size).From((page - 1) * size).Do(context.Background())
	show(res, err)
}

func show(res *elastic.SearchResult, err error) {
	if err != nil {
		return
	}
	var typ QQqun
	for _, item := range res.Each(reflect.TypeOf(typ)) {
		t := item.(QQqun)
	}
}

func query() {
	res, err := client.Search("软").Type("QQqun").Do(context.Background())
	q := elastic.NewQueryStringQuery("QQnum:3")
	res, err = client.Search("<UNK>").Type("QQqun").Query(q).Do(context.Background())
}

func main() {

}
