"""
@author June
@time 2025/8/6
@description:
"""
import struct
import threading
import time
from serial import Serial

def int2byte(v: int) -> bytes:
    return struct.pack('B', v)

def byte2float(v: bytes) -> float:
    return struct.unpack('f', v)[0]

def float2byte(v: float) -> bytes:
    return struct.pack('f', v)


HEAD = 0x7a
END = 0x7b
def make_protocol(cmd, data):
    protocol = 0
    data_len = len(data)
    protocol += HEAD
    protocol += data_len
    check = cmd + data_len
    for i in data:
        protocol += i
        check += i
    protocol += check
    protocol += END
    return protocol


def make_pid_protocol(idx: int, p: float, i: float, d: float):
    cmd = 0x01
    data = []
    data.append(idx)
    v = float2byte(p)
    for i in range(4):
        data.append(v[i])

    v = float2byte(i)
    for i in range(4):
        data.append(v[i])

    v = float2byte(d)
    for i in range(4):
        data.append(v[i])

    return make_protocol(cmd, data)




def recv():
    while 1:
        b = ser.read(1)
        print(b)

if __name__ == '__main__':
    protcol = make_pid_protocol(0, 1.0, 2.0, 3.0)
    for p in protcol:
        print("0x{:02x}", format(p), end=" ")
    print("")

    ser = Serial(port="COM5", baudrate=9600)
    ser.write("hello".encode("utf-8"))

    threading.Thread(target=recv).start()
    ser.write(bytearray(protcol))

    time.sleep(10)