/*
Package jsonxmltemplate

	@author: June
	@since: 2025/7/18
	@desc:
*/
package jsonxmltemplate

import (
	"fmt"
	"html/template"
)

func main() {
	tOk := template.New("fieldname example")
	template.Must(tOk.Parse(" some static text /* and a comment */"))
	fmt.Println("the first one parsed ok")

	template.Must(template.New("second").Parse(" some static text {{.Name}}"))
	fmt.Println("the second one parsed ok")
	fmt.Println("the next one ought to fail")

	tErr := template.New("check parse error with Must")
	template.Must(tErr.Parse("{{.Name}}"))
}
