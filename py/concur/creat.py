import time
from multiprocessing import Process


def func(num):
    for i in range(num):
        pass
    print(time.time())

#windows下 创建进程是以模块导入的形式创建
#不放在main下 每次导入都会重新创建一个进程
if __name__ == '__main__':
    num_list = [1000000, 10000000, 100000000]
    p_list = []
    print(time.time())
    for i in num_list:
        p = Process(target=func, args=(i,))
        p_list.append(p)
        p.start()
        # p.join() #主进程等待结束之后才能执行 变串行
    for i in p_list:
        i.join() #等待子进程结束
    # print(time.time())