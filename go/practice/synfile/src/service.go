package main

import "fmt"

func Get_notification(user string) chan string {
	notification := make(chan string)
	go func() {
		notification <- fmt.Sprintf("hello %s", user)
	}()
	return notification
}

func main() {
	user1 := Get_notification("zx")
	user2 := Get_notification("ls")
	fmt.Println(<-user1)
	fmt.Println(<-user2)
}
