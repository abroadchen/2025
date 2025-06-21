package webPageGet

type WebGet struct {
	Url     string
	Getfunc []func(url string) []string
}
