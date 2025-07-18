/*
Package jsonxmltemplate

	@author: June
	@since: 2025/7/18
	@desc:
*/
package jsonxmltemplate

import (
	"html/template"
	"os"
)

type Person struct {
	UserName string
}

func main() {
	t := template.New("fieldname example")
	t, _ = t.Parse(`hello {{.UserName}}!`)
	p := Person{UserName: "jinzhu"}
	t.Execute(os.Stdout, p)
}
