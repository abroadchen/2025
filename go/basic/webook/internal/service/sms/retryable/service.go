package retryable

import (
	"basic/webook/internal/service/sms"
	"context"
)

type Service struct {
	svc      sms.Service
	retryCnt int
}

func (s Service) Send(ctx context.Context, tpl string, args []string, number ...string) error {
	//TODO implement me
	err := s.svc.Send(ctx, tpl, args, number...)
	for err != nil && s.retryCnt < 10 {
		err = s.svc.Send(ctx, tpl, args, number...)
		s.retryCnt++
	}
	return err
}
