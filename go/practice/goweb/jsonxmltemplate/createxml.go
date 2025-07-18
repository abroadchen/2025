/*
Package jsonxmltemplate

	@author: June
	@since: 2025/7/18
	@desc:
*/
package jsonxmltemplate

import (
	"encoding/xml"
	"fmt"
	"os"
)

type Servers struct {
	XMLName xml.Name  `xml:"servers"`
	Version string    `xml:"version,attr"`
	Svs     []server2 `xml:"server"`
}

type server2 struct {
	ServerName string `xml:"serverName"`
	ServerIP   string `xml:"serverIP"`
}

func main() {
	v := &Servers{
		Version: "1.0",
	}
	v.Svs = append(v.Svs, server2{
		ServerName: "test1",
		ServerIP:   "127.0.0.1",
	})
	output, err := xml.MarshalIndent(v, "", "  ")
	if err != nil {
		fmt.Printf("err: %v\n", err)
	}
	os.Stdout.Write([]byte(xml.Header))
	os.Stdout.Write(output)
}
