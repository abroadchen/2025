import os

res = os.path.abspath(__file__)
print(res)
# 获取上级目录
pre = os.path.dirname(res)

v3 = os.path.join(pre, "CE.txt", "CE1.txt")