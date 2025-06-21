package logic

import (
	"context"
	"github.com/zeromicro/go-zero/core/logx"
	"user/api/internal/svc"
	"user/api/internal/types"
	"user/rpc/userclient"
)

type UserInfoLogic struct {
	logx.Logger
	ctx    context.Context
	svcCtx *svc.ServiceContext
}

func NewUserInfoLogic(ctx context.Context, svcCtx *svc.ServiceContext) *UserInfoLogic {
	return &UserInfoLogic{
		Logger: logx.WithContext(ctx),
		ctx:    ctx,
		svcCtx: svcCtx,
	}
}

func (l *UserInfoLogic) UserInfo(req *types.UserReq) (resp *types.UserResp, err error) {
	// todo: add your logic here and delete this line
	getUserResp, err := l.svcCtx.User.GetUser(l.ctx, &userclient.GetUserReq{
		Id: req.Id,
	})
	if err != nil {
		return nil, err
	}
	return &types.UserResp{
		Id:    getUserResp.Id,
		Name:  getUserResp.Name,
		Phone: getUserResp.Phone,
	}, nil
	//return &types.UserResp{
	//	Id:    "666",
	//	Name:  "",
	//	Phone: "",
	//}, nil
}
