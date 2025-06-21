package static

import "allmachinelog/mysql"

var Mydb *mysql.MySQLclient = mysql.NewMySQLclient("", "", "", "")
var Id int = 0
