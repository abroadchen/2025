package spider

import "fmt"

func Worker(id int, jobs <-chan int, results chan<- string) {
	for url := range jobs {
		tmplist := GetEmail(url)
		for _, email := range tmplist {
			results <- email
		}
	}
}

func main() {
	jobs := make(chan string, 100)
	results := make(chan string, 100)
	go func() {
		Bfs()
	}()
	for {
		fmt.Println(<-results)
	}
}
