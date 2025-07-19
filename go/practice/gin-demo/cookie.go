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
	"net/http"
)

func AuthMiddleware() gin.HandlerFunc {
	return func(c *gin.Context) {
		if cookie, err := c.Request.Cookie("cookie"); err == nil {
			if cookie.Value == "123" {
				c.Next()
				return
			}
		}
		c.JSON(http.StatusUnauthorized, gin.H{
			"error": "Unauthorized",
		})
		c.Abort()
		return
	}
}

func main() {
	r := gin.Default()
	r.GET("/cookie", func(c *gin.Context) {
		cookie, err := c.Cookie("cookie")
		if err != nil {
			cookie = ""
			c.SetCookie(
				"cookie",
				"cookie",
				-1,
				"/",
				"",
				false,
				false)
		} else {
			fmt.Println(err)
		}
		fmt.Println(cookie)
	})
}
