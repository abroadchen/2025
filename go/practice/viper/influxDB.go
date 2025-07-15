/*
Package viper

	@author: chen
	@since: 2025/7/14
	@desc:
*/
package viper

import (
	"context"
	"fmt"
	"github.com/influxdata/influxdb-client-go/v2"
	client "github.com/influxdata/influxdb1-client/v2"
	"log"
	"math/rand"
	"time"
)

func connInflux() client.Client {
	cli, err := client.NewHTTPClient(client.HTTPConfig{
		Addr:     "http://localhost:8086",
		Username: "admin",
		Password: "admin",
	})
	if err != nil {
		fmt.Println(err)
	}
	return cli
}

func queryDB(cli client.Client, cmd string) (res []client.Result, err error) {
	q := client.Query{
		Command:  cmd,
		Database: "test",
	}
	if resp, err := cli.Query(q); err == nil {
		if resp.Error() != nil {
			return res, resp.Error()
		}
		res = resp.Results
	} else {
		return res, err
	}
	return res, nil
}

func writePoints(cli client.Client) {
	bp, err := client.NewBatchPoints(client.BatchPointsConfig{
		Database:  "test",
		Precision: "s",
	})
	if err != nil {
		fmt.Println(err)
	}
	tags := map[string]string{"cpu": "ih-cpu"}
	fields := map[string]interface{}{
		"idle":   201.1,
		"system": 43.3,
		"user":   86.6,
	}
	pt, err := client.NewPoint("cpu", tags, fields, time.Now())
	if err != nil {
		fmt.Println(err)
	}
	bp.AddPoint(pt)
	err = cli.Write(bp)
	if err != nil {
		fmt.Println(err)
	}
	log.Println("insert cpu success")
}

func main() {
	client := influxdb2.NewClient("http://localhost:8086", "my-token")
	writeAPI := client.WriteAPIBlocking("my-org", "my-bucket")
	p := influxdb2.NewPoint("stat",
		map[string]string{"unit": "temperature"},
		map[string]interface{}{"avg": 24.5, "max": 45.0},
		time.Now())
	writeAPI.WritePoint(context.Background(), p)

	line := fmt.Sprintf("stat, unit=temperature avg=%f,max=%f", 24.5, 45.0)
	writeAPI.WriteRecord(context.Background(), line)

	queryAPI := client.QueryAPI("my-org")
	result, err := queryAPI.Query(context.Background(), `from(bucket:"my-bucket")|> range(start: -1h) |> filter(fn: (r) => r._measurement == "cpu")`)
	if err != nil {
		for result.Next() {
			if result.TableChanged() {
				log.Println(result.TableMetadata().String())
			}
			fmt.Printf("%s \n", result.Record().String())
		}
		if result.Err() != nil {
			fmt.Println(result.Err().Error())
		}
	}
	client.Close()
}

func read() {
	client := influxdb2.NewClient("http://localhost:8086", "my-token")
	writeAPI := client.WriteAPIBlocking("my-org", "my-bucket")
	errorsCh := writeAPI.Errors()

	go func() {
		for err := range errorsCh {
			fmt.Println(err.Error())
		}
	}()
	for i := 0; i < 100; i++ {
		p := influxdb2.NewPointWithMeasurement("stat").
			AddTag("id", fmt.Sprintf("rack_%v", i%10)).
			AddTag("vendor", "AWS").
			AddTag("hostname", fmt.Sprintf("host_%v", i%100)).
			AddField("temperature", rand.Float64()*80.0).
			AddField("disk_free", rand.Float64()*1000.0).
			AddField("disk_total", (i/10+1)*10000000).
			AddField("mem_total", (i/100+1)*10000000).
			AddField("mem_free", rand.Uint64()).
			SetTime(time.Now())
		writeAPI.WritePoint(context.Background(), p)
	}
	writeAPI.Flush(context.Background())
	client.Close()
}

func write() {
	client := influxdb2.NewClientWithOptions("http://localhost:8086", "my-token", influxdb2.DefaultOptions().SetBatchSize(20))
	writeAPI := client.WriteAPI("my-org", "my-bucket")
	for i := 0; i < 100; i++ {
		p := influxdb2.NewPoint("system",
			map[string]string{
				"id":       fmt.Sprintf("rack_%v", i%10),
				"vender":   "AWS",
				"hostname": fmt.Sprintf("host_%v", i%100),
			},
			map[string]interface{}{
				"temperature": rand.Float64() * 80.0,
				"disk_free":   rand.Float64() * 1000.0,
				"disk_total":  (i/10 + 1) * 10000000,
				"mem_total":   (i/100 + 1) * 10000000,
				"mem_free":    rand.Uint64(),
			},
			time.Now())
		writeAPI.WritePoint(p)
	}
	writeAPI.Flush()
	client.Close()
}
