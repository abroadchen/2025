package di

import (
	"crypto/tls"
	"crypto/x509"
	"log"
	"os"
)

func main() {
	cert, err := tls.LoadX509KeyPair("client.pem", "client.key")
	if err != nil {
		log.Fatal(err)
		return
	}
	certBytes, err := os.ReadFile("client.pem")
	if err != nil {
		panic("failed to read client certificate")
	}
	clientCertPool := x509.NewCertPool()
	ok := clientCertPool.AppendCertsFromPEM(certBytes)
	if !ok {
		panic("failed to parse client certificate")
	}
	conf := &tls.Config{
		RootCAs:            clientCertPool,
		Certificates:       []tls.Certificate{cert},
		InsecureSkipVerify: true,
	}
	conn, err := tls.Dial("tcp", "127.0.0.1:443", conf)
	if err != nil {
		log.Println(err)
		return
	}
	defer conn.Close()
	n, err := conn.Write([]byte("hello world"))
	if err != nil {
		log.Println(err)
		return
	}
	buf := make([]byte, 10)
	n, err = conn.Read(buf)
	if err != nil {
		log.Println(err)
		return
	}
	println(string(buf[:n]))
}
