/*
Package Flyweight

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Flyweight

var imgflyfac *ImageFlyweightFac

type ImageFlyweightFac struct {
	maps map[string]*ImageFlyweight
}

func GetImageFlyweightFac() *ImageFlyweightFac {
	if imgflyfac == nil {
		imgflyfac = &ImageFlyweightFac{
			maps: make(map[string]*ImageFlyweight),
		}
	}
	return imgflyfac
}

func (img *ImageFlyweightFac) GetMap(filename string) *ImageFlyweight {
	imag := img.maps[filename]
	if imag == nil {
		imag = NewImageFlyweight(filename)
		img.maps[filename] = imag
	}
	return imag
}
