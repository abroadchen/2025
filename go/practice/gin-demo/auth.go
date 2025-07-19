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
	"github.com/go-playground/locales/en"
	"github.com/go-playground/locales/zh"
	"github.com/go-playground/locales/zh_Hant_TW"
	ut "github.com/go-playground/universal-translator"
	en_translations "gopkg.in/go-playground/validator.v9/translations/en"
	zh_translations "gopkg.in/go-playground/validator.v9/translations/zh"
	zh_tw_translations "gopkg.in/go-playground/validator.v9/translations/zh_tw"
	"strings"

	//"github.com/go-playground/validator/v10"
	"gopkg.in/go-playground/validator.v9"
)

var (
	Uni      *ut.UniversalTranslator
	Validate *validator.Validate
)

type User struct {
	Username string `form:"username" validate:"required"`
	Tagline  string `form:"tagline" validate:"required,lt=10"`
	Tagline2 string `form:"tagline2" validate:"required,gt=1"`
}

func main() {
	en := en.New()
	zh := zh.New()
	zh_tw := zh_Hant_TW.New()
	Uni = ut.New(en, zh, zh_tw)
	Validate = validator.New()

	route := gin.Default()
	route.GET("/user/:name", func(c *gin.Context) {})
}

func startPage2(c *gin.Context) {
	local := c.DefaultQuery("local", "zh")
	trans, _ := Uni.GetTranslator(local)

	switch local {
	case "zh":
		zh_translations.RegisterDefaultTranslations(Validate, trans)
		break
	case "en":
		en_translations.RegisterDefaultTranslations(Validate, trans)
		break
	case "zh_tw":
		zh_tw_translations.RegisterDefaultTranslations(Validate, trans)
		break
	default:
		zh_tw_translations.RegisterDefaultTranslations(Validate, trans)
		break
	}

	Validate.RegisterTranslation("required", trans, func(ut ut.Translator) error {
		return ut.Add("required", "{0} must have a value!", true)
	}, func(ut ut.Translator, fe validator.FieldError) string {
		t, _ := ut.T("required", fe.Field())
		return t
	})

	user := User{}
	c.ShouldBind(&user)
	fmt.Println(user)
	err := Validate.Struct(user)
	if err != nil {
		errs := err.(validator.ValidationErrors)
		sliceErrs := []string{}
		for _, e := range errs {
			sliceErrs = append(sliceErrs, e.Translate(trans))
		}
		c.String(200, fmt.Sprintf("Validation error: %s", strings.Join(sliceErrs, "\n")))
	}
	c.String(200, fmt.Sprintf("User: %s", user.Username))
}
