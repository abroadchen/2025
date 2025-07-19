/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc: enctype="multipart/form-data"
*/
package gin_demo

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"net/http"
)

func main() {
	r := gin.Default()
	r.MaxMultipartMemory = 8 << 20

	r.LoadHTMLGlob("templates/*")
	r.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.tmpl", nil)
	})

	r.POST("/upload", func(c *gin.Context) {
		file, err := c.FormFile("file")
		if err != nil {
			c.String(500, err.Error())
		}
		c.SaveUploadedFile(file, "./upload/"+file.Filename)
		c.String(200, fmt.Sprintf("'%s' uploaded!", file.Filename))
	})

	r.POST("/uploadfiles", func(c *gin.Context) {
		form, err := c.MultipartForm()
		files := form.File["files"]
		if err != nil {
			c.JSON(http.StatusBadRequest, gin.H{
				"error": err,
			})
			return
		}
		for _, file := range files {
			fmt.Printf("%s uploaded!\n", file.Filename)
			c.SaveUploadedFile(file, "./upload/"+file.Filename)
		}
		c.JSON(http.StatusOK, gin.H{
			"message": "success",
		})
	})

}
