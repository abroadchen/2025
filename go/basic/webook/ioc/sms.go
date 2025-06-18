package ioc

import (
	"basic/webook/internal/service/sms"
	"basic/webook/internal/service/sms/memory"
)

func InitSMSService() sms.Service {
	return memory.NewService()
}
