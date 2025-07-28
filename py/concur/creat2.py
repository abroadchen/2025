import time
from threading import Thread, Lock

num = 100

mutex = Lock()
def func(mu):
    global num
    mu.acquire()
    n = num
    time.sleep(1) #会释放gil锁
    num = n - 1
    mu.release()

if __name__ == '__main__':
    t_list = []
    for i in range(100):
        t = Thread(target=func)
        t_list.append(t)
        t.start()

    for i in t_list:
        i.join()
