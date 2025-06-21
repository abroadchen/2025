package database

type SaveData interface {
	WriteLine(email string)
	WriteLines(emails []string)
}
