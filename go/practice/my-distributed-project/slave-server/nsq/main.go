/*
Package nsq

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package nsq

import (
	"fmt"
	"strconv"
)

func main() {
	for i := 0; i < 3; i++ {
		go func(j int) {
			myp := NewMyProduct()
			for i := 0; i < 100; i++ {
				myp.Pub("xx", ""+strconv.Itoa(j)+strconv.Itoa(i))
			}
		}(i)
	}

	for i := 0; i < 2; i++ {
		go func(j int) {
			myc := NewMyConsumer("xx", "channel")
			fmt.Println(myc, j)

		}(i)
	}
}
