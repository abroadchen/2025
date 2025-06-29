package test

type URLGet interface{}

type URLGETS struct {
	url    string
	mygets []func(url string) []string
}

func main() {
	myurl := new(URLGETS)
	myurl.url = ""
	myurl.mygets = []func(url string) []string{GetURL, GetMail}
	myurl.mygets[0](myurl.url)
	myurl.mygets[1](myurl.url)
}
