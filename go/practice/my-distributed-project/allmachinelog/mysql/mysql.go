package mysql

import (
	"allmachinelog/log"
	"database/sql"
	"fmt"
)

type MySQLclient struct {
	selfsql    *sql.DB
	dbhostip   string
	dbusername string
	dbpassword string
	dbname     string
}

func NewMySQLclient(ip string, username string, pwd string, dbname string) *MySQLclient {
	mysqlclient := new(MySQLclient)
	var err error
	mysqlclient.selfsql, err = sql.Open("mysql", username+":"+pwd+"@tcp("+ip+")/"+dbname)
	if err != nil {
		return nil
	}
	return mysqlclient
}

func (mysqlclient *MySQLclient) Add(info *log.LogInfo) error {

	stmt, err := mysqlclient.selfsql.Prepare("insert log set id=?,addr=?,time=?,info=?,level=?")
	if err != nil {
		return err
	}
	res, err := stmt.Exec(info.Id, info.Addr, info.Time, info.Info, info.Level)
	if err != nil {
		return err
	}
	id, err := res.LastInsertId()
	if err != nil {
		return err
	}
	if err != nil {
		fmt.Println("插入数据失败")
		return err
	} else {
		fmt.Println("插入数据成功：", id)
		return nil
	}
	return nil
}

func (mysqlclient *MySQLclient) Getall() (string, error) {
	rows, err := mysqlclient.selfsql.Query("SELECT * FROM log")
	if err != nil {
		return "", err
	} else {
		returnstr := ""
		for rows.Next() {
			var id int
			var addr string
			var time string
			var info string
			var level int
			err = rows.Scan(&id, &addr, &time, &info, &level)
			mystr := fmt.Sprintf("%d,%s, %s, %s, %d\n", id, addr, time, info, level)
			returnstr += mystr
		}
		return returnstr, nil
	}
}

func (mysqlclient *MySQLclient) Close() {
	mysqlclient.selfsql.Close()
}
