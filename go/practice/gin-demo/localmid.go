/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

func MiddleWare() gin.HandlerFunc {
	return func(c *gin.Context) {}
}

func main() {
	r := gin.Default()
	r.GET("/", MiddleWare(), func(c *gin.Context) {
		req, _ := c.Get("request")
		fmt.Println(req.(string))
		c.JSON(200, gin.H{})
	})
}
