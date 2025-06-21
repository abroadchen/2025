package database

import (
	"bufio"
	"fmt"
	"os"
	"sync"
)

type SafeFile struct {
	mutex    *sync.Mutex
	safefile *os.File
}

func NewSafeFile(path string) *SafeFile {
	var sf = new(SafeFile)
	sf.mutex = new(sync.Mutex)
	sf.safefile, _ = os.Create(path)
	return sf
}

func (sf *SafeFile) WriteLine(line string) {
	sf.mutex.Lock()
	save := bufio.NewWriter(sf.safefile)
	fmt.Fprintln(save, line)
	save.Flush()
	sf.mutex.Unlock()
}

func (sf *SafeFile) WriteLines(lines []string) {
	sf.mutex.Lock()
	save := bufio.NewWriter(sf.safefile)
	for _, line := range lines {
		fmt.Fprintln(save, line)
	}
	save.Flush()
	sf.mutex.Unlock()
}

func (sf *SafeFile) Close() {
	sf.safefile.Close()
	sf.mutex = nil
}
