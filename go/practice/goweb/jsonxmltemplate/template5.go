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
	"os"
	"strings"
)

func EmailDealWith(args ...interface{}) string {
	ok := false
	var s string
	if len(args) == 1 {
		s, ok = args[0].(string)
	}
	if !ok {
		s = fmt.Sprint(args...)
	}
	substrs := strings.Split(s, "@")
	if len(substrs) != 2 {
		return ""
	}
	return (substrs[0] + " at " + substrs[1])
}

func main() {
	f1 := Friend{Fname: "ruby"}
	f2 := Friend{Fname: "ruby2"}
	t := template.New("fieldname example")
	t = t.Funcs(template.FuncMap{
		"EmailDealWith": EmailDealWith,
	})
	t, _ = t.Parse(`
		hello {{ .UserName }}!
		{{range .Emails}}
		an email {{ . }}
		{{end}}
		{{with .Friends}}
		{{range .}}
		my friend name is {{ .Fname }}
		{{end}}
		{{end}}
	`)
	p := Person2{
		UserName: "john",
		Emails:   []string{""},
		Friends:  []*Friend{&f1, &f2},
	}
	t.Execute(os.Stdout, p)
}
