package mail

import (
	"fmt"
	"github.com/klauspost/compress/zip"
	"os"
)

func CompressZip(needcompresspath string, oucompresspath string) {
	var dir = needcompresspath
	f, err := os.ReadDir(dir)
	if err != nil {
		fmt.Println(err)
	}
	fzip, _ := os.Create(oucompresspath)
	w := zip.NewWriter(fzip)
	defer w.Close()
	for _, file := range f {
		fw, _ := w.Create(file.Name())
		filecontent, err := os.ReadFile(dir + file.Name())
		if err != nil {
			fmt.Println(err)
		}
		n, err := fw.Write(filecontent)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(n)
	}
}
