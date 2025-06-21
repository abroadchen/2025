package error

import (
	"fmt"
	"os"
)

func CheckError(err error) {
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

type Chanerr struct {
	Err    string
	Mychan chan string
}

func (e *Chanerr) Error() string {
	return fmt.Sprintf("%s", e.Err)
}
