/*
Package jsonxmltemplate

	@author: June
	@since: 2025/7/18
	@desc: jQuery 模版引擎
*/
package jsonxmltemplate

import (
	"fmt"
	"html/template"
	"os"
)

func main() {
	s1, _ := template.ParseFiles("header.tmpl", "content.tmpl")
	s1.ExecuteTemplate(os.Stdout, "header", nil)
	fmt.Println()
	s1.ExecuteTemplate(os.Stdout, "content", nil)
	fmt.Println()
	s1.ExecuteTemplate(os.Stdout, "footer", nil)
	fmt.Println()
	s1.Execute(os.Stdout, nil)
}
