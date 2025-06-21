package main

import (
	"fmt"
	"net/http"
	"os"
	"text/template"
)

func homePage(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Serving", r.Host, "for", r.URL.Path)
	myT := template.Must(template.ParseGlob("home.gohtml"))
	myT.ExecuteTemplate(w, "home.gohtml", nil)
}

func listAll(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Listing the contents of the KV store!")
	fmt.Fprintf(w, "<a href=\"/\" style=\"margin-right: 20px;\">Home sweet home!</a>")
	fmt.Fprintf(w, "<a href=\"/list\" style=\"margin-right: 20px;\">List all elements!</a>")
	fmt.Fprintf(w, "<a href=\"/change\" style=\"margin-right: 20px;\">Change an element!</a>")
	fmt.Fprintf(w, "<a href=\"/insert\" style=\"margin-right: 20px;\">Insert new element!</a>")
	fmt.Fprintf(w, "<h1>The contents of the KV store are:</h1>")
	fmt.Fprintf(w, "<ul")
	for k, v := range DATA {
		fmt.Fprintf(w, "<li>")
		fmt.Fprintf(w, "<strong>%s</strong> with value:%v\n", k, v)
		fmt.Fprintf(w, "</li>")
	}
	fmt.Fprintf(w, "</ul>")
}

func changeElement(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Changing an element of the KV store!")
	tmpl := template.Must(template.ParseFiles("change.gohtml"))
	if r.Method != http.MethodPost {
		tmpl.Execute(w, nil)
		return
	}
	key := r.FormValue("key")
	n := myElement{
		Name:    r.FormValue("name"),
		Surname: r.FormValue("surname"),
		Id:      r.FormValue("id"),
	}
	if !CHANGE(key, n) {
		fmt.Println("update operation failed!")
	} else {
		err := save()
		if err != nil {
			fmt.Println(err)
			return
		}
		tmpl.Execute(w, struct {
			Success bool
		}{true})
	}
}

func insertElement(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Inserting an element of the KV store!")
	tmpl := template.Must(template.ParseFiles("insert.gohtml"))
	if r.Method != http.MethodPost {
		tmpl.Execute(w, nil)
		return
	}
	key := r.FormValue("key")
	n := myElement{
		Name:    r.FormValue("name"),
		Surname: r.FormValue("surname"),
		Id:      r.FormValue("id"),
	}
	if !ADD(key, n) {
		fmt.Println("insert operation failed!")
	} else {
		err := save()
		if err != nil {
			fmt.Println(err)
			return
		}
		tmpl.Execute(w, struct{ Success bool }{true})
	}
}

func main() {
	err := load()
	if err != nil {
		fmt.Println(err)
	}
	PORT := ":8081"
	arguments := os.Args
	if len(arguments) != 1 {
		PORT = ":" + arguments[1]
	}
	fmt.Println("using port number", PORT)

	http.HandleFunc("/", homePage)
	http.HandleFunc("/list", listAll)
	http.HandleFunc("/change", changeElement)
	http.HandleFunc("/insert", insertElement)
	err = http.ListenAndServe(PORT, nil)
	if err != nil {
		fmt.Println(err)
	}
}
