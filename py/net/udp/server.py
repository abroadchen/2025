from socket import SOCK_DGRAM, AF_INET, socket


server = socket(AF_INET, SOCK_DGRAM)
server.bind(("127.0.0.1", 8080))
data_info, client_addr = server.recvfrom(1024)
res = data_info.decode('utf-8')
server.sendto(res.encode("utf-8"), client_addr)