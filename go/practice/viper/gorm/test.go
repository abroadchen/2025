/*
Package gorm

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package gorm

import (
	"errors"
	"fmt"
	"gorm.io/driver/mysql"
	"gorm.io/gorm"
	"time"
)

type User struct {
	ID         int64
	Username   string `gorm:"column:username"`
	Password   string `gorm:"column:password"`
	CreateTime int64  `gorm:"column:create_time"`
}

func (u User) TableName() string {
	return "users"
}

func main() {
	username := "root"
	password := "123456"
	host := "localhost"
	port := "3306"
	Dbname := "walrus"
	dsn := fmt.Sprintf("%s:%s@tcp(%s:%s)/%s", username, password, host, port, Dbname)
	db, err := gorm.Open(mysql.Open(dsn), &gorm.Config{})
	if err != nil {
		panic(err)
	}

	u := User{
		Username:   username,
		Password:   password,
		CreateTime: time.Now().Unix(),
	}
	if err := db.Create(&u).Error; err != nil {
		fmt.Println(err)
		return
	}

	u = User{}
	result := db.Where("username = ?", u.Username).First(&u)
	if errors.Is(result.Error, gorm.ErrRecordNotFound) {
		fmt.Println("can not find user")
		return
	}

	db.Model(&User{}).Where("username = ?", u.Username).Update("password", u.Password)
	db.Where("username = ?", u.Username).Delete(&User{})

}
