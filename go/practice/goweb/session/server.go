/*
Package session

	@author: June
	@since: 2025/7/18
	@desc:
*/
package session

import (
	"crypto/md5"
	"fmt"
	"html/template"
	"io"
	"net/http"
	"time"
)

var globalSessions *Manager

func init() {
	globalSessions, _ = NewManager("memory", "gosessionid", 3600)
	fmt.Println(globalSessions)
}

func login(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Login")
	sess := globalSessions.SessionStart(w, r)
	r.ParseForm()
	if r.Method == "GET" {
		t, _ := template.ParseFiles("templates/login.html")
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		t.Execute(w, sess.Get("username"))
	} else {
		sess.Set("username", r.Form["username"])
		http.Redirect(w, r, "/", 302)
	}
}

func count(w http.ResponseWriter, r *http.Request) {
	fmt.Println("count")
	sess := globalSessions.SessionStart(w, r)
	fmt.Println(sess)

	//1 防止会话劫持
	h := md5.New()
	salt := ""
	io.WriteString(h, salt+time.Now().String())
	token := fmt.Sprintf("%x", h.Sum(nil))
	if r.Form["token"][0] != token {

	}
	sess.Set("token", token)
	//2
	createtime := sess.Get("createtime")
	if createtime == nil {
		sess.Set("createtime", time.Now().Unix())
	} else if (createtime.(int64) + 60) < time.Now().Unix() {
		globalSessions.SessionDestroy(w, r)
		sess = globalSessions.SessionStart(w, r)
	}

	ct := sess.Get("countnum")
	if ct == nil {
		sess.Set("countnum", 1)
	} else {
		sess.Set("countnum", ct.(int)+1)
	}
	fmt.Println("countnum:", sess.Get("countnum"))
	t, _ := template.ParseFiles("templates/count.html")
	w.Header().Set("Content-Type", "text/html; charset=utf-8")
	t.Execute(w, sess.Get("countnum"))
}

func main() {
	http.HandleFunc("/login", login)
	http.HandleFunc("/count", count)
	http.ListenAndServe(":8080", nil)
}
