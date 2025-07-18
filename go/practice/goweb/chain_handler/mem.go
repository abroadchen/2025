/*
Package chain_handler

	@author: June
	@since: 2025/7/18
	@desc:
*/
package chain_handler

import "fmt"

type Post struct {
	Id      int
	Title   string
	Content string
	Author  string
}

var PostById map[int]*Post
var PostByAuthor map[string][]*Post

func store(post Post) {
	PostById[post.Id] = &post
	PostByAuthor[post.Author] = append(PostByAuthor[post.Author], &post)
}

func main() {
	PostById = make(map[int]*Post)
	PostByAuthor = make(map[string][]*Post)

	post1 := Post{
		Id:      1,
		Content: "hello world",
		Author:  "tom",
	}
	store(post1)
	fmt.Println(PostById[1])

	for _, post := range PostByAuthor[""] {
		fmt.Println(post)
	}
}
