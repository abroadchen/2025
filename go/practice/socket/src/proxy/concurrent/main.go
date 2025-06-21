package main

import "runtime"

func main() {
	StartConcurrentProxy("", "8081", false, true, runtime.NumCPU())
}
