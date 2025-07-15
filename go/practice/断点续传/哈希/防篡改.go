/*
@author: chen
@since: 2025/7/14
@desc:
*/
package 哈希

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
)

func main1() {
	password := "xx"
	h1 := md5.New()
	h1.Write([]byte(password))
	fmt.Println(hex.EncodeToString(h1.Sum(nil)))
	fmt.Printf("%x\n", h1.Sum(nil))
}

func main() {
	str1 := ""
	var input string
	fmt.Scanln(&input)
	h1 := md5.New()
	h1.Write([]byte(input))
	str2 := hex.EncodeToString(h1.Sum(nil))
	if str1 == str2 {
		fmt.Println("匹配成功")
	} else {
		fmt.Println("匹配失败")
	}
}
