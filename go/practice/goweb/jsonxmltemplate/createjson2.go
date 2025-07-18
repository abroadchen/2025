/*
Package jsonxmltemplate

	@author: June
	@since: 2025/7/18
	@desc:
*/
package jsonxmltemplate

import (
	"encoding/json"
	"os"
)

type Server2 struct {
	ID          int    `json:"-"` //不会导入到JSON
	ServerName  string `json:"serverName"`
	ServerName2 string `json:"serverName2,string"`
	ServerIP    string `json:"serverIP,omitempty"`
}

func main() {
	s := Server2{
		ID:          1,
		ServerName:  "serverName",
		ServerName2: "serverName2",
		ServerIP:    "127.0.0.1",
	}
	b, _ := json.Marshal(s)
	os.Stdout.Write(b)
}
