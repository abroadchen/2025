package logic

type User struct {
	Id    string
	Name  string
	Phone string
}

var users = map[string]*User{
	"1": {
		Id:    "1",
		Name:  "sss",
		Phone: "13800138000",
	},
	"2": {
		Id:    "2",
		Name:  "ssssss",
		Phone: "13800138000",
	},
}
