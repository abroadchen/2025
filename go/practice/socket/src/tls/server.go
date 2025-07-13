package tls

import (
	"crypto/rand"
	"crypto/tls"
	"crypto/x509"
	"log"
	"os"
)

func main() {
	ca_b, _ := os.ReadFile("ca.pem")
	ca, _ := x509.ParseCertificate(ca_b)
	priv_b, _ := os.ReadFile("ca.key")
	priv, _ := x509.ParsePKCS1PrivateKey(priv_b)

	pool := x509.NewCertPool()
	pool.AddCert(ca)

	cert := tls.Certificate{
		Certificate: [][]byte{ca_b},
		PrivateKey:  priv,
	}

	config := tls.Config{
		ClientAuth:   tls.RequireAndVerifyClientCert,
		Certificates: []tls.Certificate{cert},
		ClientCAs:    pool,
	}
	config.Rand = rand.Reader
	service := "0.0.0.0:443"
	listener, err := tls.Listen("tcp", service, &config)
	if err != nil {
		log.Fatalf("server: listen: %s", err)
	}
	log.Print("server: listening on", listener.Addr())

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Fatalf("server: accept: %s", err)
			break
		}
		defer conn.Close()
		log.Print("server: accepted new connection", conn.RemoteAddr())
		go handleClient(conn)
	}
}
