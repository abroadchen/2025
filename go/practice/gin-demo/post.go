/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import "github.com/gin-gonic/gin"

func main() {
	r := gin.Default()
	r.POST("/post", func(c *gin.Context) {
		username := c.PostForm("username")
		address := c.PostForm("address")

		c.JSON(200, gin.H{
			"username": username,
			"address":  address,
		})
	})
}
