/*
Package Template

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Template

import "fmt"

type HttpDownLoader struct {
	*template
}

func NewHttpDownLoader() Downloader {
	downloader := &HttpDownLoader{}
	template := Newtemplate(downloader)
	downloader.template = template
	return downloader
}

func (hd *HttpDownLoader) download() {
	fmt.Printf("http download %s\n", hd.url)
}
func (hd *HttpDownLoader) save() {
	fmt.Println("http save")
}
