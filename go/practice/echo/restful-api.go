/*
Package echo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package echo

import (
	"github.com/dgrijalva/jwt-go"
	"github.com/labstack/echo/v4"
	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
	"net/http"
	"strconv"
	"time"
)

type (
	User struct {
		ID        bson.ObjectId `json:"id" bson:"_id,omitempty"`
		Email     string        `json:"email" bson:"email"`
		Password  string        `json:"password,omitempty" bson:"password"`
		Token     string        `json:"token,omitempty" bson:"-"`
		Followers []string      `json:"followers,omitempty" bson:"followers,omitempty"`
	}
)

type (
	Post struct {
		ID      bson.ObjectId `json:"id" bson:"_id,omitempty"`
		To      string        `json:"to" bson:"to"`
		From    string        `json:"from" bson:"from"`
		Message string        `json:"message" bson:"message"`
	}
)

type (
	Handler struct {
		DB *mgo.Session
	}
)

const (
	key = "secret"
)

func (h *Handler) Signup(c echo.Context) (err error) {
	u := &User{
		ID: bson.NewObjectId(),
	}
	if err := c.Bind(u); err != nil {
		return
	}

	if u.Email == "" || u.Password == "" {
		return echo.NewHTTPError(http.StatusBadRequest, "email or password is empty")
	}

	db := h.DB.Clone()
	defer db.Close()
	if err := db.DB("twitter").C("users").Insert(u); err != nil {
		return
	}
	return c.JSON(http.StatusOK, u)
}

func (h *Handler) Login(c echo.Context) (err error) {
	u := new(User)
	if err := c.Bind(u); err != nil {
		return
	}

	db := h.DB.Clone()
	defer db.Close()
	if err = db.DB("twitter").C("users").Find(bson.M{"email": u.Email, "password": u.Password}).One(u); err != nil {
		if err == mgo.ErrNotFound {
			return &echo.HTTPError{
				Code:    http.StatusUnauthorized,
				Message: "invalid email or password",
			}
		}
		return
	}

	token := jwt.New(jwt.SigningMethodHS256)
	claims := token.Claims.(jwt.MapClaims)
	claims["id"] = u.ID
	claims["exp"] = time.Now().Add(time.Hour * 72).Unix()

	u.Token, err = token.SignedString([]byte(key))
	if err != nil {
		return
	}

	u.Password = ""
	return c.JSON(http.StatusOK, u)
}

func (h *Handler) Follow(c echo.Context) (err error) {
	userID := userIDFromToken(c)
	id := c.Param("id")

	db := h.DB.Clone()
	defer db.Close()
	if err = db.DB("twitter").C("users").UpdateId(bson.ObjectIdHex(id), bson.M{"$addToSet": bson.M{"followers": userID}}); err != nil {
		if err == mgo.ErrNotFound {
			return echo.ErrNotFound
		}
	}
	return
}

func userIDFromToken(c echo.Context) string {
	user := c.Get("user").(*jwt.Token)
	claims := user.Claims.(jwt.MapClaims)
	return claims["id"].(string)
}

func (h *Handler) CreatePost(c echo.Context) (err error) {
	u := &User{
		ID: bson.ObjectIdHex(userIDFromToken(c)),
	}
	p := &Post{
		ID:   bson.NewObjectId(),
		From: u.ID.Hex(),
	}
	if err := c.Bind(p); err != nil {
		return
	}

	if p.To == "" || p.Message == "" {
		return echo.NewHTTPError(http.StatusBadRequest, "invalid to or message fields")
	}

	db := h.DB.Clone()
	defer db.Close()
	if err := db.DB("twitter").C("users").FindId(u.ID).One(u); err != nil {
		if err == mgo.ErrNotFound {
			return echo.ErrNotFound
		}
		return
	}

	if err := db.DB("twitter").C("posts").Insert(p); err != nil {
		return
	}
	return c.JSON(http.StatusCreated, p)
}

func (h *Handler) FetchPost(c echo.Context) (err error) {
	userID := userIDFromToken(c)
	page, _ := strconv.Atoi(c.QueryParam("page"))
	limit, _ := strconv.Atoi(c.QueryParam("limit"))

	if page == 0 {
		page = 1
	}
	if limit == 0 {
		limit = 20
	}

	posts := []*Post{}
	db := h.DB.Clone()
	if err = db.DB("twitter").C("posts").Find(bson.M{"to": userID}).Skip((page - 1) * limit).Limit(limit).All(&posts); err != nil {
		return
	}
	defer db.Close()
	return c.JSON(http.StatusOK, posts)
}
