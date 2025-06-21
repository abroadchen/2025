package database

import (
	"database/sql"
	"fmt"
)

type EmailData struct {
	Email string
	Isok  int
}

func NewEmailData(email string, isok int) *EmailData {
	mydata := new(EmailData)
	mydata.Email = email
	mydata.Isok = isok
	return mydata
}

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

func (mysqlclient *MySQLclient) Add(info *EmailData) error {

	stmt, err := mysqlclient.selfsql.Prepare("insert xx set Email=?,Isok=?")
	if err != nil {
		return err
	}
	res, err := stmt.Exec(info.Email, info.Isok)
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

func (mysqlclient *MySQLclient) Getall() (string, int, int, error) {
	rows, err := mysqlclient.selfsql.Query("SELECT * FROM log")
	if err != nil {
		return "", 0, 0, err
	} else {
		returnstr := ""
		allnum := 0
		oknum := 0
		for rows.Next() {
			var id int
			var email string
			var isok int
			err = rows.Scan(&id, &email, &isok)
			mystr := fmt.Sprintf("%d,%s,%d\n", id, email, isok)
			returnstr += mystr
			allnum += 1
			if isok == 1 {
				oknum += 1
			}
		}
		return returnstr, allnum, oknum, nil
	}
}

func (mysqlclient *MySQLclient) Close() {
	mysqlclient.selfsql.Close()
}

func (mysqlclient *MySQLclient) WriteLine(email string) {
	myinfo := NewEmailData(email, 0)
	mysqlclient.Add(myinfo)
}

func (mysqlclient *MySQLclient) WriteLines(emails []string) {
	for _, mail := range emails {
		mysqlclient.WriteLine(mail)
	}
}
