package memmerge

import (
	"container/list"
	"fmt"
)

func Merge(arr []string) string {
	path := ""
	myList := list.New()
	for i := 0; i < len(arr); i++ {
		myList.PushBack(arr[i])
	}
	fmt.Println(myList.Len(), myList)

	for myList.Len() != 1 {
		e1 := myList.Back()
		myList.Remove(e1)
		e2 := myList.Back()
		myList.Remove(e2)
		fmt.Println(myList.Len(), myList)

		if e1 != nil && e2 != nil {
			v1, _ := e1.Value.(string)
			v2, _ := e2.Value.(string)
			v3 := v1 + v2
			MergeFileDisk(path+"QQ"+v1+".txt", path+"QQ"+v2+".txt", path+"QQ"+v3+".txt")
			fmt.Println(path + "QQ" + v3 + ".txt")
			myList.PushBack(v3)
		} else if e1 != nil && e2 == nil {
			v1, _ := e1.Value.(string)
			myList.PushBack(v1)
		} else if e1 == nil && e2 == nil {
			break
		} else {
			break
		}
	}
	return myList.Back().Value.(string)
}
