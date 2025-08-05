"""
@author June
@time 2025/8/3
@description:
"""
import socket


def get_local_ip():
    local_ips = ["127.0.0.1"]
    for ip in socket.gethostbyname_ex(socket.gethostname())[2]:
        if ip not in local_ips:
            local_ips.append(ip)
    return local_ips


def decode_data(bytes_arr:  bytes) -> str:
    try:
        msg = bytes_arr.decode("utf-8")
    except UnicodeDecodeError:
        msg = bytes_arr.decode("gbk")
    return msg