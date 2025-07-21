/*
Package Memo

	@author: June
	@since: 2025/7/20
	@desc:
*/
package Memo

type MMfeel struct {
	tall     int
	rich     int
	handsome int
}

var state []MMfeel = make([]MMfeel, 0)

type MMoldfeel struct {
	tall     int
	rich     int
	handsome int
}

func (mfe *MMfeel) firstmeet(tall, rich, handsome int) {
	mfe.tall = tall
	mfe.rich = rich
	mfe.handsome = handsome
	state = append(state, *mfe)
}
func (mfe *MMfeel) korea() {
	mfe.handsome += 30
	state = append(state, *mfe)
}
func (mfe *MMfeel) lottery() {
	mfe.rich += 5000000
	state = append(state, *mfe)
}
func (mfe *MMfeel) score() {}
