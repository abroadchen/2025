package search

type Search interface {
	GetQQQunByWord(word []string, filename string) []string
}
