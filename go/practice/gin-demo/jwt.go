/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import (
	"fmt"
	"github.com/casbin/casbin"
	xormadapter "github.com/casbin/xorm-adapter"
	"github.com/gin-gonic/gin"
	_ "github.com/go-sql-driver/mysql"
)

func main() {
	a := xormadapter.NewAdapter("mysql", "root:root@tcp(127.0.0.1:3306)/goblog?charset=utf8", true)

	e := casbin.NewEnforcer("conf/rbac_model.conf", a)

	e.LoadPolicy()

	r := gin.New()
	r.POST("/api/v1/add", func(c *gin.Context) {
		fmt.Println("add policy")
		if ok := e.AddPolicy("admin", "/api/v1/hello", "GET"); !ok {
			fmt.Println("add policy failed")
		} else {
			fmt.Println("add policy success")
		}
	})

	r.DELETE("/api/v1/delete", func(c *gin.Context) {
		fmt.Println("delete policy")
		if ok := e.RemovePolicy("admin", "/api/v1/hello", "GET"); !ok {
			fmt.Println("delete policy failed")
		} else {
			fmt.Println("delete policy success")
		}
	})

	r.GET("/api/v1/get", func(c *gin.Context) {
		fmt.Println("get policy")
		list := e.GetPolicy()
		for _, vlist := range list {
			for _, v := range vlist {
				fmt.Println(v)
			}
		}
	})

	r.Use(Authorize(e))
	r.GET("/api/v1/login", func(c *gin.Context) {
		fmt.Println("get policy")
	})
	r.Run(":8080")
}

func Authorize(e *casbin.Enforcer) gin.HandlerFunc {
	return func(c *gin.Context) {
		obj := c.Request.URL.RequestURI()
		act := c.Request.Method
		sub := "admin"

		if ok := e.Enforce(sub, obj, act); ok {
			fmt.Println("authorize success")
			c.Next()
		} else {
			fmt.Println("authorize failed")
			c.Abort()
		}
	}
}
