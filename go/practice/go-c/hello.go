/*
Package main

	@author: June
	@since: 2025/7/22
	@desc:
*/
package main

import "C"
import "fmt"

//export SayHello
func SayHello(s *C.char) {
	fmt.Printf("Hello, %s!\n", C.GoString(s))
}
