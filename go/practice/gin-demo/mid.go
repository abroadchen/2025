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

func main() {
	r := gin.Default()
	r.Use(gin.Logger())
	r.Use(gin.Recovery())

	authorized := r.Group("/authorized")
	authorized.Use(AuthRequired())
	{
		authorized.POST("/upload", func(c *gin.Context) {})
	}

}

func AuthRequired() gin.HandlerFunc {
	return func(c *gin.Context) {
		fmt.Println("middleware start")
		fmt.Println("", c.Request)
		c.Set("username", "admin")
		c.Next()
		fmt.Println("middleware end")
	}
}
