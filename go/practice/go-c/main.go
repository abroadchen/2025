/*
Package go_c

	@author: June
	@since: 2025/7/22
	@desc:
*/
package main

/*
#include <stdio.h>

static void SayHello(const char *s)
{
	puts(s);
}
*/

//#include <stdio.h>
// void SayHello(const char *s);
import "C"

func main() {
	println("hello cgo")
	C.puts(C.CString("hello world"))
}
