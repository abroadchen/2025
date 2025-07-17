/*
Package crawl

	@author: chen
	@since: 2025/7/15
	@desc: 框架
*/
package crawl

import (
	"fmt"
	"github.com/fern4lvarez/go-metainspector/metainspector"
)

func main() {
	url := "http://www.cloudcontrol.com/pricing"
	MI, err := metainspector.New(url)
	if err != nil {
		fmt.Printf("Error: %v", err)
	} else {
		fmt.Printf("\nURL: %s\n", MI.Url())
		fmt.Printf("Scheme: %s\n", MI.Scheme())
		fmt.Printf("Host: %s\n", MI.Host())
		fmt.Printf("Root: %s\n", MI.RootURL())
		fmt.Printf("Title: %s\n", MI.Title())
		fmt.Printf("Language: %s\n", MI.Language())
		fmt.Printf("Author: %s\n", MI.Author())
		fmt.Printf("Description: %s\n", MI.Description())
		fmt.Printf("Charset: %s\n", MI.Charset())
		fmt.Printf("Feed URL: %s\n", MI.Feed())
		fmt.Printf("Links: %v\n", MI.Links())
		fmt.Printf("Images: %v\n", MI.Images())
		fmt.Printf("Keywords: %v\n", MI.Keywords())
		fmt.Printf("Compatibility: %v\n", MI.Compatibility())
	}
}
