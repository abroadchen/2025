package main

import "flag"

var (
	cidr string
)

func init() {
	flag.StringVar(&cidr, "cidr", "192.168.0.0/24", "CIDR to use")
}

func main() {
	flag.Parse()
}
