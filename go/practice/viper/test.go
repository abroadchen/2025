/*
Package viper

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package viper

import (
	"fmt"
	"net/http"
)

import (
	"github.com/fsnotify/fsnotify"
	"github.com/gin-gonic/gin"
	"github.com/spf13/viper"
)

type Config struct {
	Port    int    `mapstructure:"port"`
	Version string `mapstructure:"version"`
}

var Conf = new(Config)

func main() {
	viper.SetConfigFile("./config.yaml")
	err := viper.ReadInConfig()
	if err != nil {
		panic(fmt.Errorf("Fatal error config file: %s \n", err))
	}
	if err := viper.Unmarshal(Conf); err != nil {
		panic(fmt.Errorf("Fatal error config file: %s \n", err))
	}
	viper.WatchConfig()
	viper.OnConfigChange(func(e fsnotify.Event) {
		fmt.Println("")
		if err := viper.Unmarshal(&Conf); err != nil {
			panic(fmt.Errorf("Fatal error config file: %s \n", err))
		}
	})
	r := gin.Default()
	r.GET("/version", func(c *gin.Context) {
		c.String(http.StatusOK, Conf.Version)
	})
	if err := r.Run(fmt.Sprintf(":%d", Conf.Port)); err != nil {
		panic(err)
	}
}
