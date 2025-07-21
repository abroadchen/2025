/*
Package Flyweight

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Flyweight

import "fmt"

type ImageViewer struct {
	*ImageFlyweight
}

func NewImageViewer(filename string) *ImageViewer {
	imag := GetImageFlyweightFac().GetMap(filename)
	return &ImageViewer{imag}
}

func (i *ImageViewer) Display() {
	fmt.Printf("image viewer is display %s\n", i.GetData())
}
