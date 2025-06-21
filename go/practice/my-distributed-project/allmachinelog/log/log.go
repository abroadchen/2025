package log

type LogInfo struct {
	Id    int    `db:"app_id"`
	Addr  string `db:"addr"`
	Time  string `db:"time"`
	Info  string `db:"info"`
	Level int    `db:"level"`
}

func NewLogInfo(Id int, Addr string, Time string, Info string, Level int) *LogInfo {
	myinfo := new(LogInfo)
	myinfo.Id = Id
	myinfo.Addr = Addr
	myinfo.Time = Time
	myinfo.Info = Info
	myinfo.Level = Level
	return myinfo
}
