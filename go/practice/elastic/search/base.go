package search

type Search interface {
	GetQQQunByWord(word []string, filename string) []string
}

type Cache interface {
	GetCache(word []string, filename string) []string
	SaveCache(word []string, filename string, saveContent []string) bool
}
