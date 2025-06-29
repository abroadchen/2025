package test

type SaveData interface {
	save(email string)
	saves(emails []string)
}

type SaveTxt struct {
	path string
}

type SaveMysql struct {
	localhost string
	port      int
	user      string
	password  string
}

func (savetxt *SaveTxt) save(email string) {

}

func (savetxt *SaveTxt) saves(email []string) {}

func main() {
	var save SaveData
	save = new(SaveTxt)
	save.save("<UNK>")
}
