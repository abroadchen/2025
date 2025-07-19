/*
Package gin_demo

	@author: June
	@since: 2025/7/19
	@desc:
*/
package gin_demo

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"github.com/sirupsen/logrus"
	"log"
	"math"
	"os"
	"time"
)

var timeFormat = "2006-01-02 15:04:05"

func Logger(logger logrus.FieldLogger) gin.HandlerFunc {
	hostname, err := os.Hostname()
	if err != nil {
		hostname = "unknown"
	}
	return func(c *gin.Context) {
		path := c.Request.URL.Path
		start := time.Now()
		c.Next()
		stop := time.Since(start)
		latency := int(math.Ceil(float64(stop.Nanoseconds()) / 1000000.0))
		statusCode := c.Writer.Status()
		clientIP := c.ClientIP()
		clientUserAgent := c.Request.UserAgent()
		referer := c.Request.Referer()
		dataLength := c.Writer.Size()
		if dataLength < 0 {
			dataLength = 0
		}

		entry := logger.WithFields(logrus.Fields{
			"hostname":   hostname,
			"statusCode": statusCode,
			"clientIP":   clientIP,
			"latency":    latency,
			"clientUser": clientUserAgent,
			"referer":    referer,
			"dataLength": dataLength,
			"path":       path,
		})

		if len(c.Errors) > 0 {
			entry.Error(c.Errors.ByType(gin.ErrorTypePrivate).String())
		} else {
			msg := fmt.Sprintf("%s - %s [%s] \"%s %s\" %d %d \"%s\" \"%s\" (%dms)", clientIP, hostname, time.Now())
			if statusCode > 499 {
				entry.Error(msg)
			} else if statusCode > 399 {
				entry.Warn(msg)
			} else {
				entry.Info(msg)
			}
		}
	}
}

func StatCost() gin.HandlerFunc {
	return func(c *gin.Context) {
		t := time.Now()
		c.Set("time", t.Format("2006-01-02 15:04:05"))
		c.Next()
		latency := time.Since(t)
		log.Println(latency)
	}
}

func main() {
	r := gin.Default()
	r.Use(StatCost(), gin.Logger())
	r.GET("/", func(c *gin.Context) {
		example := c.MustGet("example").(string)
		log.Println(example)
		c.JSON(200, gin.H{
			"example": example,
		})
	})
}
