/*
Package 分布式存储

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package 分布式存储

import (
	"fmt"
	"github.com/astaxie/beego/httplib"
	"io"
	"net/http"
	"os"
)

/*
Upload

	@Description:  ?download=0
*/
func Upload(filepath string) string {
	var obj interface{}
	req := httplib.Post("http://127.0.0.1:8080/upload")
	req.PostFile("file", filepath)
	req.Param("output", "json")
	req.Param("scene", "")
	req.Param("path", "")
	req.ToJSON(&obj)
	fmt.Println(obj)
	url := obj.(map[string]interface{})["url"].(string)
	fmt.Println(url)
	return url
}

/*
Download

	@Description:
	@param url
	@param savepath
	@return bool
*/
func Download(url string, savepath string) bool {
	res, err := http.Get(url)
	if err != nil {
		fmt.Println(err)
		return false
	}
	f, err := os.Create(savepath)
	if err != nil {
		fmt.Println(err)
		return false
	}
	io.Copy(f, res.Body)
	defer f.Close()
	return true
}
