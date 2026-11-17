//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
from math import gcd
from sys import stdout
from random import randint

n = int(input())//读入要分解的整数 n

cand = [6,7,3]

for t in range(50) :
    x = randint(0, n - 1)
    print("sqrt", x * x % n)
    stdout.flush()
    y = int(input())
    if x == y :
        continue
    if x < y :
        [x, y] = [y, x]
    x -= y
    cand.append(x)
    cand.append(n // x)

primes = []

while n != 1 :
    p = n
    for x in cand :
        y = gcd(p, x)
        if y != 1 :
            p = y
    for x in cand :
        if x % p == 0 :
            x //= p
    primes.append(p)
    n //= p
    print(p)

print("!", len(primes), " ".join(map(str, primes)))

cand（candidate）是候选因子列表，先放入 3 个初始小因子。之后每次取样会往里面追加新的候选。
之所以先用固定小数字，是为了确保至少有几个"稳"的因子候选可参与 gcd
做 50 轮随机取样。次数固定为 50 是经验值——多轮能显著提高拆出大质因子的概率
随机挑一个 [0, n-1] 的整数 x
向裁判发送命令 sqrt (x² mod n)。
必须 flush，交互题否则裁判等不到消息会超时（重要）
读回裁判返回的平方根 y，它满足 y² ≡ x² (mod n)
如果 y == x，说明输出的是平凡平方根（没有新信息），跳过本轮
保证 x >= y（把大的放前面，交换）。
x = x - y。根据同余理论：因为 x² ≡ y² (mod n)，所以 n | (x² - y²) = (x-y)(x+y)。
于是 x - y 与 n 的 gcd 很可能是 n 的一个非平凡因子
把 x-y（记为 x 重赋值后）和 n // (x-y) 都收进候选列表。
因为 n | (x-y)(x+y)，所以 n / (x-y) 里也藏着另一个因子
存放分解出的质因数。
只要 n 还没被吃完，就继续抽因子。
第一次扫描：把 cand 里每个候选与 p 求 gcd，收敛出一个因子 p（吸收所有与 n 有公共因子的候选）。
效果：把分散在各候选里的共同因子，通过 gcd 逐步合并成一个非平凡因子 p
记录质因数 p，n 除以 p，并把 p 打印给裁判。
最后向裁判宣告：! 质因数个数 各质因数（空格分隔），完成交互。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 50;
int main() {
    fast;
    return 0;
}