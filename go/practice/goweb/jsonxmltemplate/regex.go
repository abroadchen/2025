/*
Package jsonxmltemplate

	@author: June
	@since: 2025/7/18
	@desc:
*/
package jsonxmltemplate

import (
	"fmt"
	"regexp"
)

func main() {
	a := ""
	re, _ := regexp.Compile("[^a-zA-Z0-9]+")
	one := re.Find([]byte(a))
	fmt.Println(string(one))

	all := re.FindAll([]byte(a), -1)
	fmt.Println(all)

	index := re.FindIndex([]byte(a))
	fmt.Println(index)

	allindex := re.FindAllIndex([]byte(a), -1)
	fmt.Println(allindex)

	re2, _ := regexp.Compile("am(.*)lang(.*)")
	submatch := re2.FindSubmatch([]byte(a))
	fmt.Println(submatch)
	for _, value := range submatch {
		fmt.Println(string(value))
	}

	submatchindex := re2.FindSubmatchIndex([]byte(a))
	fmt.Println(submatchindex)
	submatchall := re2.FindAllSubmatch([]byte(a), -1)
	fmt.Println(submatchall)
	submatchallindex := re2.FindAllSubmatchIndex([]byte(a), -1)
	fmt.Println(submatchallindex)
}
