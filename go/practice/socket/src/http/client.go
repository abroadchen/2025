package main

import (
	"fmt"
	"net/http"
)

func main() {
	resp, err := http.Get("http://www.baidu.com")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer resp.Body.Close()

	//file, err := os.Create("test.txt")
	//if err != nil {
	//	fmt.Println(err)
	//	return
	//}
	//defer file.Close()
	//io.Copy(file, resp.Body)

	//client := http.Client{
	//	//Timeout: time.Second * 5,
	//	Transport: &http.Transport{
	//		DisableKeepAlives: true,
	//		Dial: (&net.Dialer{
	//			Timeout: 30 * time.Second,
	//		}).Dial,
	//	},
	//}
	//resp, err = client.Get("http://www.baidu.com")
	//if err != nil {
	//	fmt.Println(err)
	//	return
	//}
	//defer resp.Body.Close()
	//io.Copy(os.Stdout, resp.Body)

	//client = &http.Client{}
	//req, err = http.NewRequest("GET", "http://www.baidu.com", nil)
	//if err != nil {
	//	fmt.Println(err)
	//	return
	//}
	//req.Header.Add("Accept", "text/plain")
	//req.Header.Add("User-Agent", "SampleClient/1.0")
	//
	//resp, err := client.Do(req)
	//if err != nil {
	//	fmt.Println(err)
	//	return
	//}
	//defer resp.Body.Close()
	//io.Copy(os.Stdout, resp.Body)

	fmt.Println("response Status:", resp.Status)
	fmt.Println("response StatusCode:", resp.StatusCode)
	fmt.Println("response Headers:", resp.Header)
	fmt.Println("response Body:", resp.Body)

	buf := make([]byte, 4096)
	var result string
	for {
		n, err := resp.Body.Read(buf)
		if err != nil {
			fmt.Println(err)
			break
		}
		result += string(buf[:n])
	}
	fmt.Println(result)
	//pagebytes, err := ioutil.ReadAll(resp.Body)
	//if err != nil {
	//	fmt.Println(err)
	//	return
	//}
	//fmt.Println(string(pagebytes))
}
