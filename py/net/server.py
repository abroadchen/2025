import socket
import struct
import subprocess
from threading import Thread

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 8080))
server.listen(5)



def func(conn):
    while True:
        cmd = conn.recv(1024).decode("utf-8")
        if cmd.__len__() == 0:
            break
        if cmd.upper() == "Q":
            break
        obj = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        std_out = obj.stdout.read()
        std_err = obj.stderr.read()
        result = (std_out + std_err)
        total_size = struct.pack('i', len(result))
        conn.send(total_size)
        conn.send(result)
    conn.close()


while True:
    conn, client_addr = server.accept()
    t = Thread(target=func, args=(conn,))
    t.start()



