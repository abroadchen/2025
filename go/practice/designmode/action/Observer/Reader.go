/*
Package Observer

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Observer

import "fmt"

type Reader struct {
	name string
}

func NewReader(name string) *Reader {
	return &Reader{name}
}

func (r *Reader) Update(s *Subject) {
	fmt.Printf("%s 收到 %s\n", r.name, s.context)
}
