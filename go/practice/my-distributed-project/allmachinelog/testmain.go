package allmachinelog

import "fmt"

func main() {
	var str string
	str = fmt.Sprintf("%d,%s", 19, "xx")
	fmt.Println(str)
	var num int
	var mystr string
	fmt.Println("num", num)
	fmt.Println("mystr", mystr)
	fmt.Sscanf(str, "%d,%s", &num, &mystr)
}
