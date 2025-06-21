package main

import (
	"encoding/gob"
	"fmt"
	"os"
)

type myElement struct {
	Name    string
	Surname string
	Id      string
}

var DATA = make(map[string]myElement)
var DATAFILE = "dataFile.gob"

func save() error {
	fmt.Println("saving dataFile", DATAFILE)
	err := os.Remove(DATAFILE)
	if err != nil {
		fmt.Println(err)
	}
	saveTo, err := os.Create(DATAFILE)
	if err != nil {
		fmt.Println("cannot create file", DATAFILE)
	}
	defer saveTo.Close()
	encode := gob.NewEncoder(saveTo)
	err = encode.Encode(DATA)
	if err != nil {
		fmt.Println("cannot encode file", DATAFILE)
		return err
	}
	return nil
}

func load() error {
	fmt.Println("loading dataFile", DATAFILE)
	loadFrom, err := os.Open(DATAFILE)
	defer loadFrom.Close()
	if err != nil {
		fmt.Println("empty key/value store")
		return err
	}
	decoder := gob.NewDecoder(loadFrom)
	decoder.Decode(&DATA)
	return nil
}

func ADD(k string, n myElement) bool {
	if k == "" {
		return false
	}
	if LOOKUP(k) == nil {
		DATA[k] = n
		return true
	}
	return false
}

func DELETE(k string) bool {
	if LOOKUP(k) != nil {
		delete(DATA, k)
		return true
	}
	return false
}

func LOOKUP(k string) *myElement {
	_, ok := DATA[k]
	if ok {
		n := DATA[k]
		return &n
	} else {
		return nil
	}
}

func CHANGE(k string, n myElement) bool {
	DATA[k] = n
	return true
}

func PRINT() {
	for k, d := range DATA {
		fmt.Println("key: %s value: %s\n", k, d)
	}
}
