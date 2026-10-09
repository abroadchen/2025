//
// Created by Psy.C on 2026/10/9.
//
/**
用双层循环 + goto 判断
i
i 是否为质数，是则加入 p。
生成
2
,
3
,
5
,
7
,
.
.
.
,
67
2,3,5,7,...,67 共 19 个不大于 70 的质数（正好对应线性基 20 位，也就是 b[20] 的理由）。
效率低（O(x²)）但 x=70 无所谓
一个 20 位的异或线性基（最高位 19 → 0），经典插入：从高位往低位，若当前位为 1 且基为空则置入并返回，否则异或消除该位。
用于求一组数异或能张成的线性空间的秩（基的个数）
对每个质因子
j
j：统计
a
a 中
j
j 的幂次奇偶，奇数次则对应二进制位为 1。
得到一个 19 位的掩码 now，表示该数所有质因子幂次的奇偶性向量。
把 now 插入线性基。
数学本质：每个数对应
G
F
(
2
)
GF(2) 上的一个向量（各质因子幂次的奇偶）。两个数相乘 = 向量异或。两数乘积为完全平方数 ⟺ 对应向量异或为 0
bs.b[i] 非 0 的个数就是线性基的秩（本质不同的基向量数）。
n 减少秩后，剩下的自由变量数为
n
−
rank
n−rank。
ksm(n) 计算
2
n
  
m
o
d
  
(
10
9
+
7
)
2
n
 mod(10
9
 +7)（快速幂，底数 2）。
结论：满足条件的非空子集数量为
2
n
−
rank
−
1
2
n−rank
 −1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

vector<int> p;
void init(int x) {
    for (int i = 2; i <= x; ++i) {
        for (int j = 2; j < i; ++j)
            if (i%j == 0) goto end;
        p.push_back(i);
        end:;
    }
}

struct node {
    int b[20];
    void insert(int x) {
        for (int i = 19; i >= 0; --i) {
            if (!(x&(1<<i))) continue;
            if (!b[i]) { b[i] = x; return; }
            x ^= b[i];
        }
    }
} bs;

int ksm(int x) {
    int ret = 1, mod = 1e9+7, a = 2;
    while (x) {
        if (x&1) ret=ret*a%mod;
        a=a*a%mod;
        x >>= 1;
    }
    return ret;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}


signed main() {
    fast;
    int n, a; rd(n); init(70);
    for (int i = 1; i <= n; ++i) {
        rd(a);
        int now = 0;
        for (int j : p) {
            now <<= 1;
            while (a%j == 0) a /= j, now ^= 1;//每个质因子出现奇数次则翻转该位
        }
        bs.insert(now);
    }
    for (int i = 19; i >= 0; --i) n -= bs.b[i] != 0;//n = n - 线性基秩(基元个数)
    cout << ksm(n)-1;
    return 0;
}