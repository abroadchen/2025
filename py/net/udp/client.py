from socket import SOCK_DGRAM, AF_INET, socket


client = socket(AF_INET, SOCK_DGRAM)
user_input = input("请输入一段内容:")
client.sendto(user_input.encode("utf-8"), ("127.0.0.1", 8080))
res, server_addr = client.recvfrom(1024)
print(res[0].decode("utf-8"))