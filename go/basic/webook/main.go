package main

import (
	"basic/webook/config"
	"basic/webook/internal/repository"
	"basic/webook/internal/repository/cache"
	"basic/webook/internal/repository/dao"
	"basic/webook/internal/service"
	"basic/webook/internal/service/sms/memory"
	"basic/webook/internal/web"
	"basic/webook/internal/web/middleware"
	"basic/webook/pkg/ginx/middlewares/ratelimit"
	"github.com/gin-contrib/cors"
	"github.com/gin-contrib/sessions"
	"github.com/gin-contrib/sessions/memstore"
	"github.com/gin-gonic/gin"
	"github.com/redis/go-redis/v9"
	"gorm.io/gorm"
	"net/http"
	"strings"
	"time"
)

func main() {
	//db := initDB()
	//u := initUser(db)
	//
	server := InitWebServer()
	//server := gin.Default()
	server.GET("/hello", func(ctx *gin.Context) {
		ctx.String(http.StatusOK, "hello world")
	})
	//u.RegisterRoutes(server.Group("/user"))
	server.Run(":8080")
}

func initWebServer() *gin.Engine {
	server := gin.Default()
	redisClient := redis.NewClient(&redis.Options{
		Addr: config.Config.Redis.Addr,
	})
	server.Use(ratelimit.NewBuilder(redisClient, time.Second, 100).Build())

	server.Use(cors.New(cors.Config{
		AllowOrigins:     []string{"http://localhost:3000"},
		AllowMethods:     []string{"POST"},
		AllowHeaders:     []string{"Content-Type", "Authorization"},
		ExposeHeaders:    []string{"x-jwt-token"},
		AllowCredentials: true,
		AllowOriginFunc: func(origin string) bool {
			if strings.HasPrefix(origin, "http://localhost") {
				return true
			}
			return strings.Contains(origin, "psy.com")
		},
		MaxAge: 12 * time.Hour,
	}))

	//store := cookie.NewStore([]byte("secret"))
	store := memstore.NewStore([]byte("HziLlveiTl71pFQyrTFsBzuZcexCR9sy"), []byte("gGUHNLr1h1t0z2GCLcmc3AuFvohJCLXt"))
	//store, err := redis.NewStore(16, "tcp", "localhost:6379", "", "", []byte("HziLlveiTl71pFQyrTFsBzuZcexCR9sy"), []byte("gGUHNLr1h1t0z2GCLcmc3AuFvohJCLXt"))
	//if err != nil {
	//	panic(err)
	//}
	//myStore := &sqlx_store.Store{}
	server.Use(sessions.Sessions("mysession", store))
	//server.Use(middleware.NewLoginMiddlewareBuilder().IgnorePaths("/users/signup").IgnorePaths("/users/login").Build())
	server.Use(middleware.NewLoginJWTMiddlewareBuilder().IgnorePaths("/users/signup").IgnorePaths("/users/login_sms/code/send").IgnorePaths("/users/login_sms").IgnorePaths("/users/login").Build())

	//middleware.IgnorePaths = []string{"/users/signup"}
	//server.Use(middleware.CheckLogin())
	//server1 := gin.Default()
	//server1.Use(middleware.CheckLogin())
	return server
}

func initUser(db *gorm.DB, rdb redis.Cmdable) *web.UserHandler {
	ud := dao.NewUserDao(db)
	uc := cache.NewUserCache(rdb)
	repo := repository.NewUserRepository(ud, uc)
	svc := service.NewUserService(repo)
	codeCache := cache.NewCodeCache(rdb)
	codeRepo := repository.NewCodeRepository(codeCache)
	smsSvc := memory.NewService()
	codeSvc := service.NewCodeService(codeRepo, smsSvc)
	u := web.NewUserHandler(svc, codeSvc)
	return u
}
