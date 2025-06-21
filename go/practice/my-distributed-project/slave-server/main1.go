package main

import (
	"net"
	"slave-server/myerror"
	"slave-server/network/threadrun"
	"slave-server/network/threadsafenetwork"
	"slave-server/staticdata"
	"slave-server/thread/mem"
)

func main() {

	if staticdata.IsMEM {
		for i := 0; i < int(staticdata.ThreadNum); i++ {
			go mem.EmailChanThread()
		}
		go mem.Monitor()
	}

	server_listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		myerror.CheckError(err)
	}
	defer server_listener.Close()
	for {
		new_conn, err := server_listener.Accept()
		if err != nil {
			myerror.CheckError(err)
		}
		go threadrun.MsgHandle(new_conn)
		if staticdata.IsMEM {
			go mem.SaveEmailChan(*threadsafenetwork.NewReturnEmail(new_conn))
		}
	}
}
