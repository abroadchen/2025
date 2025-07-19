/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import (
	"github.com/gin-gonic/gin"
	"net/http"
)

func main() {
	r := gin.Default()
	r.GET("/somJSON", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"message": "somJSON",
			"status":  http.StatusOK,
		})
	})

	r.GET("/moreJSON", func(c *gin.Context) {
		var msg struct {
			Name    string
			Message string
			Number  int
		}
		msg.Name = "hello"
		msg.Message = "hello"
		msg.Number = 1
		c.JSON(http.StatusOK, msg)
		c.XML(http.StatusOK, msg)
	})
}
