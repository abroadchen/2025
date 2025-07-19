/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import "github.com/gin-gonic/gin"

func index(c *gin.Context) {
	c.JSON(200, gin.H{
		"message": "index",
	})
}

func search(c *gin.Context) {
	c.JSON(200, gin.H{
		"message": "search",
	})
}

func support(c *gin.Context) {
	c.JSON(200, gin.H{
		"message": "support",
	})
}

func main() {
	r := gin.Default()
	v1 := r.Group("/v1")
	{
		v1.POST("/index", index)
		v1.POST("/search", search)
	}
}
