package main

import (
	"fmt"
	"net/url"
	"strings"
)

func main() {
	s := "postgres://user:password@host.com:5432/path?k=v#f"
	v, err := url.Parse(s)
	if err != nil {
		panic(err)
	}
	fmt.Println(v.Scheme)
	fmt.Println(v.User)
	fmt.Println(v.User.Username())
	p, _ := v.User.Password()
	fmt.Println(p)
	fmt.Println(v.Host)
	h := strings.Split(v.Host, ":")
	fmt.Println(h[0])
	fmt.Println(h[1])
	fmt.Println(v.Path)
	fmt.Println(v.Fragment)
	fmt.Println(v.RawQuery)
	m, _ := url.ParseQuery(v.RawQuery)
	fmt.Println(m)
	fmt.Println(m["k"][0])
}
