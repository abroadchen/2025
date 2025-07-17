/*
Package group

	@author: June
	@since: 2025/7/17
	@desc:
*/
package group

import "fmt"

func main() {
	var s []int
	for i := 0; i < 100000; i++ {
		go func(n int) {
			s = append(s, n)
		}(i)
	}
	fmt.Printf("%v\n", s[0])
}
