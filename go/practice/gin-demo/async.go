/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import (
	"github.com/gin-gonic/gin"
	"log"
	"time"
)

func main() {
	r := gin.Default()
	r.GET("/", func(c *gin.Context) {
		copyContext := c.Copy()

		go func() {
			time.Sleep(1 * time.Second)
			log.Println("" + copyContext.Request.URL.Path)
		}()
	})
}
