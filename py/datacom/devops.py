"""
@author June
@time 2025/7/28
@description:
"""
from datetime import datetime
import os
import re
import time
from threading import Thread

import paramiko
from ncclient import manager
from ncclient.xml_ import to_ele

from config import switch_info, parameter_command, host_log, netconf_info
class SwitchMonitor:
    def __init__(self, **kwargs):
        self.ip =  kwargs['ip']
        self.port = kwargs['port']
        self.username = kwargs['username']
        self.password = kwargs['password']
        self.sysname = kwargs['sysname']
        self.ssh_session = None
        self.vty = None

    def transport(self):
        ssh_session = paramiko.SSHClient()
        ssh_session.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh_session.connect(self.ip,
                            self.port,
                            self.username,
                            self.password,
                            allow_agent=False,
                            look_for_keys=False)
        self.ssh_session = ssh_session


    def open_vty(self):
        if not self.ssh_session:
            self.transport()
        self.vty = self.ssh_session.invoke_shell()
        self.vty.send('screen-length 0 temporary\n')




    def download(self):
        if not self.vty:
            self.open_vty()
        for i in ["save\n", "Y\n"]:
            self.vty.send(i)
            time.sleep(1)
        # self.vty.send("save\n")
        # time.sleep(1)
        # self.vty.send("Y\n")
        # time.sleep(1)
        tran = paramiko.Transport((self.ip, self.port))
        tran.connect(username=self.username, password=self.password)
        sftp = paramiko.SFTPClient.from_transport(tran)

        now = datetime.now().strftime("%Y_%m_%d")
        res = "{}_{}.zip".format(now, self.sysname)
        remote_path = "/vrpcfg.zip"
        local_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), res)
        sftp.get(remote_path, local_path)
        sftp.close()


    def parameter_get(self, parameter):
        if not self.vty:
            self.open_vty()
        self.vty.send(parameter_command[parameter]['command'])
        time.sleep(1)
        content = self.vty.recv(999999).decode('utf-8')
        pat = re.compile(parameter_command[parameter]['re'])

        res = pat.findall(content)
        if parameter == "fan_state":
            res = res if res else "all fans are fault"
        return res

    def netconf(self,  xml_content, **kwargs):
        with manager.connect(host=kwargs['ip'],
                            port=kwargs['port'],
                            username=kwargs['username'],
                            password=kwargs['password'],
                            look_for_keys=False,
                            allow_agent=False,
                            device_params={'name': 'default'},
                            hostkey_verify=False) as m:
            content = to_ele(xml_content)
            m.rpc(content)
        print("%s exec success time is %s"%(xml_content, datetime.now().strftime("%Y-%m-%d %H:%M:%S")))


    def parameter_monitor(self):
        while True:
            res = "\n".join( ["{}:{}".format(key, self.parameter_get(key)) for key in ["cpu_usage", "power", "fan_state", "ospf_state", "memory_usage", "lacp_state"]])
            time_first = time.time()
            yield res
            time_last = time.time()
            if (time_last - time_first) < 5*60:
                time.sleep(5*60 - (time_last - time_first))


    def parameter_over(self):
        p = self.parameter_monitor()
        while True:
            print(next(p))


    def download_monitor(self):
        while True:
            current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            set_datetime = """
            <sys::set-current-datetime xmlns::sys="urn:ietf:params:xml:ns:yang:ietf-system">
                <sys:current-datetime>%s</sys:current-datetime>
            </sys:set-current-datetime>
            """ % current_time
            self.netconf(**netconf_info, xml_content=set_datetime)
            self.download()
            time_first = time.time()
            yield "backup finished, time is " % current_time
            time_last = time.time()
            if (time_last - time_first) < 24*60:
                time.sleep(24*60 - (time_last - time_first))

    def download_over(self):
        d = self.parameter_monitor()
        while True:
            print(next(d))

    def periodic_statistics(self):
        t1 = Thread(target=self.parameter_over)
        t2 = Thread(target=self.download_over)
        t1.start()
        t2.start()



if __name__ == '__main__':

    a = SwitchMonitor(**switch_info)
    a.netconf(**netconf_info, xml_content=host_log)
    a.periodic_statistics()