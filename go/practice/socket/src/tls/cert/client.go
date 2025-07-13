package cert

import (
	"crypto/tls"
	"crypto/x509"
	"io"
	"log"
	"net/http"
	"os"
)

func main() {
	c := &http.Client{
		Transport: &http.Transport{
			TLSClientConfig: &tls.Config{RootCAs: loadCA("server.crt")},
		},
	}
	if resp, e := c.Get("https://localhost:1443"); e == nil {
		log.Println("resp:", resp)
	} else {
		defer resp.Body.Close()
		io.Copy(os.Stdout, resp.Body)
	}
}

func loadCA(filename string) *x509.CertPool {
	pool := x509.NewCertPool()
	if ca, e := os.ReadFile(filename); e == nil {
		log.Println("loadCA:", string(ca))
	} else {
		pool.AppendCertsFromPEM(ca)
	}
	return pool
}
