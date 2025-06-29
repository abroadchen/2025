package proxy

import (
	"io"
	"io/ioutil"
	"net/http"
	"os"
)

type whoiam struct {
	Addr string
}

func main() {
	url := "http://127.0.0.1:8080/"
	if "" != os.Getenv("URL") {
		url = os.Getenv("URL")
	}
	log.Printf("Target %s", url)
	resp, err := http.Get(url + "/whoyouare")
	if nil != err {
		log.Fatal(err.Error())
	}
	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)
	if nil != err {
		log.Fatal(err.Error())
	}
	println("You are", string(body))
}
