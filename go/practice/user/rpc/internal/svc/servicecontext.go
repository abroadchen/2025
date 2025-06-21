package svc

import (
	"user/models"
	"user/rpc/internal/config"
)

type ServiceContext struct {
	Config    config.Config
	UserModel models.UsersModel
}

func NewServiceContext(c config.Config) *ServiceContext {
	//sqlConn := sqlx.NewMysql(c.MySql.DataSource)
	return &ServiceContext{
		Config: c,
		//UserModel: models.NewUsersModel(sqlConn, c.Cache),
	}
}
