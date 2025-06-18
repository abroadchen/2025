//go:build wireinject

package main

import (
	"basic/webook/internal/repository"
	"basic/webook/internal/repository/cache"
	"basic/webook/internal/service"
	"basic/webook/internal/web"
	"basic/wire/repository/dao"
	"github.com/gin-gonic/gin"
	"github.com/google/wire"
)

func InitWebServer() *gin.Engine {
	wire.Build(InitDB, InitRedis,
		dao.NewUserDAO,
		cache.NewUserCache,
		cache.NewCodeCache,
		repository.NewUserRepository,
		repository.NewCodeRepository,
		service.NewUserService,
		service.NewCodeService,
		InitSMSService,
		web.NewUserHandler,
		InitGin,
		InitMiddlewares)
	return new(gin.Engine)
}
