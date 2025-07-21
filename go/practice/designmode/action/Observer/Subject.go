/*
Package Observer

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Observer

type Subject struct {
	obs     []Observer
	context string
}

func NewSubject() *Subject {
	return &Subject{make([]Observer, 0), ""}
}

func (s *Subject) notify() {
	for _, o := range s.obs {
		o.Upddate(s)
	}
}

func (s *Subject) UpdateContext(context string) {
	s.context = context
	s.notify()
}

func (s *Subject) Attach(o Observer) {
	s.obs = append(s.obs, o)
}
