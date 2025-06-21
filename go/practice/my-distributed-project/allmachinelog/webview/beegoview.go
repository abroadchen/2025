package webview

import (
	"allmachinelog/static"
	"github.com/astaxie/beego"
)

type MainController struct {
	beego.Controller
}

func (c *MainController) Get() {
	mystr, _ := static.Mydb.Getall()
	c.Ctx.WriteString(mystr)
}

func main() {
	beego.Router("/", &MainController{})
	beego.Run()
}
