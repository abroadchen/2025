package network

import "net/http"

func TestHTTP() error {
	_, err := http.Get("http://www.baidu.com")
	return err
}
