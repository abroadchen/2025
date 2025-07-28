import subprocess

while True:
    cmd = input("请输入需要执行的命令:")
    if cmd.upper() == "Q":
        break
    obj = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    std_out = obj.stdout.read()
    std_err = obj.stderr.read()
    result = (std_out+std_err).decode("GBK")
    print(result)