import re
import time

import paramiko


class SSH:
    def __init__(self, host: str, port: int, username: str, password: str) -> None:
        self.ip = host
        self.port = port
        self.username = username
        self.password = password
        self.ssh_session = None
        self.vty = None
        self.mark = None
        self.login = False
        self.config = False
        self.old_mark = None

    def transport(self) -> None:
        ssh_session = paramiko.SSHClient()
        ssh_session.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh_session.connect(self.ip, self.port, self.username, self.password)
        self.ssh_session = ssh_session

    def open_vty(self) -> None:
        if not self.ssh_session:
            self.transport()
        self.vty = self.ssh_session.invoke_shell()


    def get_mark(self, arg: str) -> None:
        pat = re.compile('<.+?>')
        res = pat.findall(arg)
        if res.__len__() == 1:
            self.mark = self.old_mark = res[0]
        else:
            raise GetMarkError(self.ip)




    def login_device(self) -> None:
        try:
            self.transport()
            self.open_vty()
        except Exception:
            raise LoginError(self.ip)
        time.sleep(1)
        content = self.vty.recv(999).decode('utf-8')
        self.get_mark(content)
        self.login = True


    def recv_result(self) -> str:
        pat = re.compile(self.mark)
        ret = ""
        while True:
            time.sleep(1)
            content = self.vty.recv(999).decode('utf-8')
            print(content)
            ret += content
            if pat.search(content):
                break
            self.vty.send(' ')
        return ret


    def send_command(self, command: str) -> str:
        if not self.login:
            self.login_device()
        self.vty.send(command + '\n')
        res = self.recv_result()
        return res


    def config_mode(self) -> None:
        if not self.login:
            self.login_device()
        self.mark = "\[.+?\]"
        self.send_command("system-view")
        self.config = True


    def exit(self) -> str:
        # self.mark = '<.+?>'
        self.mark = self.old_mark
        return self.send_command("return")


    def config_command(self, command: list) -> str:
        if not self.config:
            self.config_mode()
        ret = ""
        for i in command:
            ret += self.send_command(i)
        ret += self.send_command("commit")
        ret += self.exit()
        return ret


class LoginError(Exception):
    def __init__(self, ip: str) -> None:
        self.ip = ip

    def __str__(self) -> str:
        return f"{self.ip} Login Error"

class GetMarkError(Exception):
    def __init__(self, ip: str) -> None:
        self.ip = ip

    def __str__(self) -> str:
        return f"{self.ip} Get Mark Error"


if __name__ == '__main__':
    a = SSH('192.168.1.1', '22', 'admin', 'admin')
    # res = a.send_command(command="dis cu")
    # print(res)
    a.config_command(["interface G1/0/0", "des ytedu"])