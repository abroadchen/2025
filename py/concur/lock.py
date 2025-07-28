import json
import random
import time
from multiprocessing import Process, Lock


def search(name):
    with open("config.txt", "r", encoding="utf-8") as f:
        dic = json.load(f)
    print("用户{}查看当前余票为{}".format(name, dic.get("ticket_num")))

def buy(name, mu):
    search(name)
    time.sleep(random.randint(1, 3))
    mu.acquire() #抢锁
    with open("config.txt", "r", encoding="utf-8") as f:
        dic = json.load(f)

    if dic.get("ticket_num") > 0:
        print("用户{}成功购买一张票".format(name))
        dic["ticket_num"] -= 1
        with open("config.txt", "w", encoding="utf-8") as f:
            json.dump(dic, f)
    else:
        print("用户{}没有票了".format(name))
    mu.release()

if __name__ == '__main__':
    mutex = Lock()
    for i in range(10):
        p = Process(target=buy, args=("用户{}".format(i), mutex))
        p.start()
