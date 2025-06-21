package main

type URLGet interface{}

type URLGET struct {
	url   string
	myget func(url string) []string
}

type SaveData interface {
	save(email string)
	saves(email []string)
}
