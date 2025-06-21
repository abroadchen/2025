package RandomStr

import (
	"crypto/md5"
	"encoding/hex"
	"math/rand"
	"time"
)

func MD5(txt string) string {
	ctx := md5.New()
	ctx.Write([]byte(txt))
	return hex.EncodeToString(ctx.Sum(nil))
}

func GetRandomSalt() string {
	return GetRandomString(8)
}

func GetRandomString(length int) string {
	str := "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	bytes := []byte(str)
	result := []byte{}
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	for i := 0; i < length; i++ {
		result = append(result, bytes[r.Intn(len(bytes))])
	}
	return string(result)
}
