// Package 哈希
//
//	@author: chen
//	@since: 2025/7/14
//	@desc:
package 哈希

import (
	"crypto/sha512"
	"fmt"
	"io"
	"os"
)

func GetFileMD5(filePath string) (string, error) {
	file, err := os.Open(filePath)
	defer file.Close()
	if err != nil {
		return "", err
	}
	md5hash := sha512.New()
	if _, err := io.Copy(md5hash, file); err != nil {
		return "", err
	}
	md5hash.Sum(nil)
	return fmt.Sprintf("%x", md5hash.Sum(nil)), nil
}
