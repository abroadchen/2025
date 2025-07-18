/*
Package form

	@author: June
	@since: 2025/7/18
	@desc:
*/
package form

import (
	"fmt"
	"html/template"
	"net/http"
	"regexp"
	"strconv"
)

func register(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	username := r.Form.Get("username")
	if username == "" {
		fmt.Println("username is empty")
		fmt.Fprintf(w, "username is empty")
	}

	age, err := strconv.Atoi(r.Form.Get("age"))
	if err != nil {
		fmt.Println("age is invalid")
		fmt.Fprintf(w, "age is invalid")
	}

	if age > 100 || age < 0 {
		fmt.Println("age is out of range")
		fmt.Fprintf(w, "age is out of range")
	}

	if m, _ := regexp.MatchString("^[0-9]+$", r.Form.Get("age")); !m {
		fmt.Println("friend is invalid")
		fmt.Fprintf(w, "friend is invalid")
	}
	//  验证中文
	if m, _ := regexp.MatchString(`^[\x{4e00}-\x{9fa5}]+$`, r.Form.Get("name")); !m {
		fmt.Println("name is invalid")
		fmt.Fprintf(w, "name is invalid")
	}

	if m, _ := regexp.MatchString(`^[a-zA-Z]+$`, r.Form.Get("friend")); !m {
		fmt.Println("friend is invalid")
		fmt.Fprintf(w, "friend is invalid")
	}

	if m, _ := regexp.MatchString(`^([\w\.\_]{2,10})@(\w{1,}).([a-z]{2,4})$`, r.Form.Get("email")); !m {
		fmt.Println("email is invalid")
		fmt.Fprintf(w, "email is invalid")
	}
	if m, _ := regexp.MatchString(`^(1[3|5|6|7|8][0-9]\d{8})$`, r.Form.Get("mobile")); !m {
		fmt.Println("mobile is invalid")
		fmt.Fprintf(w, "mobile is invalid")
	}
	// 下拉菜单
	xx := r.Form.Get("xx")
	res1 := checkSelect(xx)
	if !res1 {
		fmt.Println("xx is invalid")
		fmt.Fprintf(w, "xx is invalid")
	}
	// 单选按钮
	sex := r.Form.Get("sex")
	res2 := checkSex(sex)
	if !res2 {
		fmt.Println("请选择正确的性别")
		fmt.Fprintf(w, "")
	}
	// 复选框
	hobby := r.Form["hobby"]
	res3 := checkHooby(hobby)
	if !res3 {
		fmt.Println("")
		fmt.Fprintf(w, "")
	}

	if m, _ := regexp.MatchString(`^(\d{17})([0-9]|x)$`, r.Form.Get("usercard")); !m {
		fmt.Println("usercard is invalid")
		fmt.Fprintf(w, "usercard is invalid")
	}

}

func checkSelect(xx string) bool {
	slice := []string{"", "", ""}
	for _, v := range slice {
		if xx == v {
			return true
		}
	}
	return false
}

func checkSex(sex string) bool {
	slice := []string{"", ""}
	for _, v := range slice {
		if v == sex {
			return true
		}
	}
	return false
}

func checkHooby(hobby []string) bool {
	slice := []string{"", ""}
	hobby2 := slice_diff(hobby, slice)

	if hobby2 == nil {
		return true
	}
	return false
}

func slice_diff(a, b []string) (diffslice []string) {
	for _, v := range a {
		if !InSlice(v, b) {
			diffslice = append(diffslice, v)
		}
	}
	return
}

func InSlice(val string, slice []string) bool {
	for _, v := range slice {
		if v == val {
			return true
		}
	}
	return false
}

func sayHello2(w http.ResponseWriter, r *http.Request) {
	//fmt.Println("method:", r.Method)
	//r.ParseForm()
	if r.Method == "GET" {
		t, _ := template.ParseFiles("register.html")
		t.Execute(w, nil)
	}
	//} else {
	//	fmt.Println("username:", r.Form["username"])
	//	fmt.Println("password:", r.Form["password"])
	//}
}

func main() {
	http.HandleFunc("/register", register)
	http.HandleFunc("/login", sayHello2)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		panic(err)
	}
}
