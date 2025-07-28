import datetime
import os.path
import time

# from pysnmp.entity.engine import SnmpEngine
from pysnmp.hlapi import *
# from pysnmp.hlapi import getCmd, SnmpEngine, CommunityData, UdpTransportTarget, ContextData, ObjectType, ObjectIdentity
import paramiko
from pysnmp.hlapi.v1arch import UdpTransportTarget
from pysnmp.hlapi.v3arch import UsmUserData, usmHMACSHAAuthProtocol, usmAesCfb128Protocol, ContextData

from pysnmp.smi.rfc1902 import ObjectType, ObjectIdentity


def transport():
    ssh_session = paramiko.SSHClient()
    ssh_session.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh_session.connect('192.168.1.1', 22, 'username', 'password')
    return ssh_session


def ssh_config():
    with open('snmp.txt', 'r', encoding='utf-8') as f:
        res = f.readlines()
        print(res)
    ssh_session = transport()
    vty = ssh_session.invoke_shell()
    # vty.send('N\n') #是否修改密码
    # time.sleep(1)
    # vty.send('system-view im\n')
    # time.sleep(1)

    vty.send("Y\n")
    time.sleep(0.5)
    vty.send("Huawei@123\n")
    time.sleep(0.5)
    vty.send("Admin@123\n")
    time.sleep(0.5)
    vty.send("Admin@123\n")
    time.sleep(0.5)




    for i in res:
        vty.send(i)
        time.sleep(0.5)
        print(vty.recv(99).decode('utf-8'))
    # res = vty.recv(99).decode('utf-8')
    # print(res)


def download(name):
    # #1
    # tran = transport()
    # res = tran.get_transport()
    # sftp = paramiko.SFTPClient.from_transport(res)
    #2
    tran = paramiko.Transport(('192.168.1.1', 22))
    tran.connect(username='username', password='password')
    sftp = paramiko.SFTPClient.from_transport(tran)
    now = datetime.now().strftime("%Y_%m_%d_%H_%M_%S")+f"_{name}"
    remot = "/vrpcfg.cfg"
    local = os.path.join(os.path.dirname(os.path.abspath(__file__)), now)
    # sftp.get(remot, local)
    remot_put = "CE.cfg"
    sftp.put(local, remot_put)
    sftp.close()




# def snmp():
# get = nextCommand(SnmpEngine(),
#        UsmUserData('admin',
#                    'Huawei@123',
#                    'Huawei@123',
#                    authProtocol=usmHMACSHAAuthProtocol,
#                    privProtocol=usmAesCfb128Protocol),
#        UdpTransportTarget(('192.168.1.1', 161)),
#        ContextData(),
#        ObjectType(ObjectIdentity('1.3.6.1.2.1.1.5.0')))
  # a, b, c, d = next(get)
    # for i in d:
    #     # print(str(i))
    #     res = str(i).split('=')[1].strip()
    # return res





if __name__ == '__main__':
    pass
    # ssh_config()
    # arg = snmp()
    # download(arg)
    # print(next(get))
