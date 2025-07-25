/*
Package gui

	@author: June
	@since: 2025/7/22
	@desc:
*/
package main

import (
	"github.com/mattn/go-gtk/gtk"
	"os"
)

func main() {
	gtk.Init(&os.Args)

	window := gtk.NewWindow(gtk.WINDOW_TOPLEVEL)
	window.SetPosition(gtk.WIN_POS_CENTER)
	window.SetTitle("GO")
	window.SetSizeRequest(1300, 2300)

	window.Show()

	gtk.Main()
}
