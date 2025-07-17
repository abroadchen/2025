/*
Package mutex

	@author: June
	@since: 2025/7/17
	@desc:
*/
package mutex

/*
or3

	@Description: slice[start:end:capacity]
	@param channels
	@return <-chan
*/
func or3(channels ...<-chan interface{}) <-chan interface{} {
	switch len(channels) {
	case 0:
		return nil
	case 1:
		return channels[0]
	}

	orDone := make(chan interface{})
	go func() {
		defer close(orDone)

		switch len(channels) {
		case 2:
			select {
			case <-channels[0]:
			case <-channels[1]:
			}
		default:
			m := len(channels) / 2
			select {
			case <-or3(append(channels[:m:m], orDone)...):
			case <-or3(append(channels[m:], orDone)...):
			}
		}

	}()
	return orDone
}
