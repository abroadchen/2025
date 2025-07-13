package sqlite

import (
	"database/sql"
	"fmt"
	"os"
)

func main() {
	os.Remove("test.db")
	db, err := sql.Open("sqlite3", ":memory:")
	if err != nil {
		fmt.Println(err)
	}
	stmt, err := db.Prepare("insert into sqlite3 (name) values (?)")
	res, err := stmt.Exec(1)
	id, err := res.LastInsertId()
	fmt.Println(id)

	stmt, err = db.Prepare("update sqlite3 SET name = ?")
	res, err = stmt.Exec(id)
	affect, err := res.RowsAffected()
	fmt.Println(affect)

	rows, err := db.Query("select * from sqlite3")
	for rows.Next() {
		var id int
		var name string
		err = rows.Scan(&id, &name)
		fmt.Println(id, name)
	}

	stmt, err = db.Prepare("delete from sqlite3 where name = ?")
	res, err = stmt.Exec(1)
	affect, err = res.RowsAffected()
	fmt.Println(affect)
	db.Close()
}
