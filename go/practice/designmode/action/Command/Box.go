/*
Package Command

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Command

type Box struct {
	WashClothes Command
	WarmBed     Command
}

func NewBox(washClothes, warmBed Command) *Box {
	return &Box{
		WashClothes: washClothes,
		WarmBed:     warmBed,
	}
}

func (b *Box) GoWashClothes() {
	b.WashClothes.Execute()
}

func (b *Box) GoWarmBed() {
	b.WarmBed.Execute()
}
