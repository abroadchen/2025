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

type Person2 struct {
	UserName string
	Emails   []string
	Friends  []*Friend
}

type Friend struct {
	Fname string
}

func main() {
	f1 := Friend{Fname: "ruby"}
	f2 := Friend{Fname: "ruby2"}
	t := template.New("fieldname example")
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
