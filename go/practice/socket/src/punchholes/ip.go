package main

import (
	"fmt"
	"net"
	"os"
)

func main11() {
	ip := net.ParseIP("127.0.0.1")
	if ip == nil {
		fmt.Println("Invalid IP")
		fmt.Println("Address should user IPv4 or IPv6")
		os.Exit(1)
	}
	fmt.Println()
	fmt.Println("IP:             %s\n", ip)
	fmt.Println("Default Mask:   %s\n", net.IP(ip.DefaultMask()))
	fmt.Println("Loopback:       %s\n", ip.IsLoopback())
	fmt.Println("Unicast:")
	fmt.Println("Global:         %s\n", ip.IsGlobalUnicast())
	fmt.Println("Link:           %s\n", ip.IsLinkLocalUnicast())
	fmt.Println("Multicast:")
	fmt.Println("Global:         %s\n", ip.IsMulticast())
	fmt.Println("Link:           %s\n", ip.IsLinkLocalMulticast())
	fmt.Println("Interface       %s\n", ip.IsInterfaceLocalMulticast())
	fmt.Println()
}

func main() {
	ip := net.ParseIP("127.0.0.1")
	if ip != nil {
		fmt.Println("%v OK\n", ip)
	} else {
		fmt.Println("Invalid IP")
	}
}
