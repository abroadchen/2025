/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import (
	"github.com/gin-gonic/gin"
	"github.com/gin-gonic/gin/testdata/protoexample"
	"net/http"
)

func main() {
	r := gin.Default()
	r.POST("/loginForm", func(c *gin.Context) {
		var form Login
		if err := c.ShouldBindXML(&form); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}

		if form.User != "" || form.Password != "" {
			c.JSON(http.StatusUnauthorized, gin.H{
				"error":  "wrong username or password",
				"status": "unauthorized",
			})
		}

		r.GET("/someXML", func(c *gin.Context) {
			c.XML(http.StatusOK, gin.H{})
		})

		r.GET("/someYAML", func(c *gin.Context) {
			c.YAML(http.StatusOK, gin.H{})
		})

		r.GET("/someProtoBuf", func(c *gin.Context) {
			reps := []int64{int64(1), int64(2)}
			label := ""
			data := &protoexample.Test{
				Label: &label,
				Reps:  reps,
			}
			c.ProtoBuf(http.StatusOK, data)
		})

		c.JSON(http.StatusOK, gin.H{
			"status": "ok",
		})
	})
}
