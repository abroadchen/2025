package mongo

type DataBase interface {
	SaveLog(datalog DataLog) error
	SaveLogs(datalog []DataLog) error
	FindLogByIP(IP string) []DataLog
	FindLogByTime(Time string) []DataLog
	FindLogByType(Type string) []DataLog
	FindLogByLevel(Level string) []DataLog
	FindLogByName(APPName string) []DataLog
	FindLogByContent(info string) []DataLog
	FindLogBySQL(sqlstr interface{}) []DataLog
	GetAll() []string
	Clear() bool
}
