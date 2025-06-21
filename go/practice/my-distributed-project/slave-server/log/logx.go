package log

import (
	"fmt"
	"log"
	"os"
	"time"
)

var dayseconds = 24 * 60 * 60

type Logfile struct {
	Filepath string
	Loger    *log.Logger
}

func Newlogfile() *Logfile {
	l := new(Logfile)
	path := "./" + time.Now().Format("2006-01-02") + ".txt"
	l.Filepath = path
	logfile, err := os.Create(path)
	if err != nil {
		fmt.Println(err)
	}
	l.Loger = log.New(logfile, "test_", log.Ldate|log.Ltime|log.Lshortfile)
	return l
}
