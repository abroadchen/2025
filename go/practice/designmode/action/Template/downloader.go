/*
Package Template

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Template

import "fmt"

type Downloader interface {
	Download(string)
}

type template struct {
	impl
	url string
}
type impl interface {
	download()
	save()
}

func Newtemplate(impl impl) *template {
	return &template{impl: impl, url: ""}
}

func (t *template) Download(url string) {
	t.url = url
	t.impl.download()
}
func (t *template) save() {
	fmt.Println("模版下载")
	t.impl.save()
}
