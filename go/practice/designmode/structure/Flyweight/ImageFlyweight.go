/*
Package Flyweight

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Flyweight

import "fmt"

type ImageFlyweight struct {
	data string
}

func NewImageFlyweight(filename string) *ImageFlyweight {
	data := fmt.Sprintf("data:image/png;base64,%s", filename)
	return &ImageFlyweight{data: data}
}

func (img *ImageFlyweight) GetData() string {
	return img.data
}
