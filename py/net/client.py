import socket
import struct

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 8080))


while True:
    user_input = input("请输入需要执行的命令(q/Q退出):").strip()
    if user_input.__len__() == 0:
        continue
    client.send(user_input.encode("utf-8"))
    if user_input.upper() == "Q":
        break
    total_size = struct.unpack('i', client.recv(4))[0]
    size = 0
    res = ""
    while size < total_size:
        res += client.recv(1024).decode("GBK")
        size += 1024
    print(res)
client.close()