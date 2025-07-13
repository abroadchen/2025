package mysql

import (
	"database/sql"
	"fmt"
	_ "github.com/go-sql-driver/mysql"
)

var db *sql.DB

func initDB() (err error) {
	dsn := "root:123456@tcp(127.0.0.1:3306)/test?charset=utf8"
	db, err = sql.Open("mysql", dsn)
	if err != nil {
		return
	}
	err = db.Ping()
	if err != nil {
		return
	}
	return nil
}

func insertRowDemo(name string, age int) {
	sqlStr := `insert into demo(name,age) values(?,?)`
	ret, err := db.Exec(sqlStr, name, age)
	if err != nil {
		fmt.Println(err)
		return
	}
	theID, _ := ret.LastInsertId()
	fmt.Println(theID)
}

func queryMultiRowDemo() {
	sqlStr := `select id,name,age from user where id > ?`
	rows, err := db.Query(sqlStr, 0)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer rows.Close()
	for rows.Next() {
		var u user
		err := rows.Scan(&u.id, &u.name, &u.age)
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println(u)
	}
}

func updateRowDemo() {
	sqlStr := `update demo set age=? where id=?`
	ret, err := db.Exec(sqlStr, 0, 0)
	if err != nil {
		fmt.Println(err)
		return
	}
	n, err := ret.RowsAffected()
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(n)
}

func main() {
	dsn := "root:123456@tcp(127.0.0.1:3306)/test?charset=utf8"
	db, err := sql.Open("mysql", dsn)
	if err != nil {
		panic(err)
	}
	defer db.Close()
}
