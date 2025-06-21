package main

import (
	"fmt"
	"net"
)

func main() {
	interfaces, err := net.Interfaces()
	if err != nil {
		fmt.Println(err)
		return
	}
	for _, i := range interfaces {
		fmt.Println("Interface %v\n", i.Name)
		byName, err := net.InterfaceByName(i.Name)
		if err != nil {
			fmt.Println(err)
			return
		}
		addr, err := byName.Addrs()
		for k, v := range addr {
			fmt.Println("Interface Address %v: %v\n", k, v.String())
		}
		fmt.Println("Interface Flags:", i.Flags.String())
		fmt.Println("Interface MTU", i.MTU)
		fmt.Println("Interface Hardware Address:", i.HardwareAddr)
	}
}
