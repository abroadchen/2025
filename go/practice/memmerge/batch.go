package memmerge

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	path := ""
	dir_list, _ := os.ReadDir(path)
	filelist := []string{}
	for i, v := range dir_list {
		fmt.Println(i, path+v.Name())
		filelist = append(filelist, strconv.Itoa(i))
	}
	fmt.Println(filelist)
	fmt.Println("merge start")
	Merge(filelist)
	fmt.Println("merge end")
}
