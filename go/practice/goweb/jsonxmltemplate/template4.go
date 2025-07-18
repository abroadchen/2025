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

func main() {
	tEmpty := template.New("fieldname example")
	tEmpty = template.Must(tEmpty.Parse("空 pipeline if demo: {{if ``}}不会输出.{{end}}\n"))
	tEmpty.Execute(os.Stdout, nil)

	tWithValue := template.New("fieldname example")
	tWithValue = template.Must(tWithValue.Parse("不为空的 pipeline if demo: {{if `anything`}}我有内容,我会输出.{{end}}\n"))
	tWithValue.Execute(os.Stdout, nil)

	tIfElse := template.New("fieldname example")
	tIfElse = template.Must(tIfElse.Parse("if-else demo: {{if `anything`}} if 部分 {{else}} else 部分.{{end}}\n"))
	tIfElse.Execute(os.Stdout, nil)
}
