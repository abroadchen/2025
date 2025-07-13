package mysql

import (
	"fmt"
	"github.com/jmoiron/sqlx"
)

func main() {
	var pool *sqlx.DB
	dsn := "root:123456@tcp(127.0.0.1:3306)/test?charset=utf8"
	pool, err := sqlx.Open("mysql", dsn)
	if err != nil {
		fmt.Println(err)
	}
	pool.SetMaxOpenConns(100)
	pool.SetMaxIdleConns(20)

	sql := "select * from user where name=? and age=?"
	pool.Queryx(sql, "", 1)

	countryCitySql := `insert into country_cities (id, name, city) values (?, ?, ?)`
	result, err := pool.Exec(countryCitySql, "", "", 11)
	if err != nil {
		fmt.Println(err)
	}
	id, _ := result.LastInsertId()
	result2 := pool.MustExec(countryCitySql, "", "", id)
	id2, _ := result2.LastInsertId()
	fmt.Println(id, id2)

	sql = `update demo set age=? where id=?`
	ret, err := db.Exec(sql, 0, 0)
	if err != nil {
		fmt.Println(err)
	}
	rowsAffected, _ := ret.RowsAffected()
	fmt.Println(rowsAffected)

	type Place struct {
		country string
		city    string
		telcode int
	}
	p := Place{}
	err = pool.Get(&p, "select * from place LIMIT ?", id)
	var total int
	err = pool.Get(&total, "select count(*) from place")
	fmt.Println(total)
}
