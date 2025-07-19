/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import "github.com/gin-gonic/gin"

func xx(c *gin.Context) {
	c.JSON(200, gin.H{
		"hello": "world",
	})
}

func main() {
	r := gin.Default()
	r.GET("/hello", xx)
	r.GET("/user/search", func(ctx *gin.Context) {
		username := ctx.DefaultQuery("username", "default")
		address := ctx.Query("address")
		ctx.JSON(200, gin.H{
			"username": username,
			"address":  address,
		})
	})

	r.GET("/user/search2/:username/:address", func(ctx *gin.Context) {
		username := ctx.Param("username")
		address := ctx.Param("address")
		ctx.JSON(200, gin.H{
			"username": username,
			"address":  address,
		})
	})
}
