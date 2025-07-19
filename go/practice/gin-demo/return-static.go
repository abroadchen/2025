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
	r.StaticFS("/static", http.Dir("static"))
}
