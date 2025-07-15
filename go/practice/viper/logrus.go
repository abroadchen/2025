/*
Package viper

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package viper

import (
	logr "github.com/sirupsen/logrus"
	"os"
)

func main1() {
	logr.WithFields(logr.Fields{
		"animal": "walrus",
	}).Info("A walrus appears")
}

func main2() {
	var log = logr.New()
	log.Out = os.Stdout
	log.WithFields(logr.Fields{
		"animal": "walrus",
		"size":   10,
	}).Info("A Walrus appears")
}

func main() {
	var log = logr.New()
	log.Out = os.Stdout
	log.WithFields(logr.Fields{
		"animal": "walrus",
		"size":   10,
	}).Info("A Walrus appears")
	log.Trace("Trace a trace")
	log.Debug("Debug a debug")
	log.Info("Info a info")
	log.Warn("Warn a warn")
	log.Error("Error a error")
	log.Fatal("Fatal a fatal")
	log.Panic("Panic a panic")
}
