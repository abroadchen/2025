//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
N = 7e3+1（值域上界 7000），M = 1e5+5（变量个数）。
s[i]：第 i 个变量的值集合，bitset（长度 7000）。s[i] 的第 v 位 = 值 v 出现次数的奇偶（mod 2）。
mu[n]：莫比乌斯函数μ(n)。
f[y]、p[y]：预处理出来的两个辅助 bitset
递推求 μ（用整除/约数关系做容斥），结果归到整数（mod 2 意义下用其非零性）
这是在构造"i 是 j 的约数"的关系：f[j] 的第 i 位为 1 ⟺
i∣j。于是 op==1 时 s[x] = f[y] 把集合设为"y 的所有因子"
p[i] 的第 j 位为 1 ⟺ i∣j 且 μ(j/i)!=0，即 j/i 是无平方因子数（square-free）。这正好是查询所要的"
y 的倍数，且倍数除以 y 为 square-free"的集合。
while 循环（四种操作）：
op==1：s[x] = f[y]，把 s[x] 置为 y 的因子集合。
op==2：s[x] = s[y] ^ s[z]，集合取对称差（异或，mod 2 相加）。
op==3：s[x] = s[y] & s[z]，集合取交集（mod 2 相乘）。
op==4：cout << ((s[x]&p[y]).count()&1)，求 s[x] 与 p[y] 交集大小，只输出其奇偶（0 或 1）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<n; ++i)
using namespace std;

constexpr int N = 7e3+1, M = 1e5+5;

bitset<N> s[M], f[N], p[N];
int n, q, mu[N];
int main() {
    fast;
    cin >> n >> q; mu[1] = 1;
    rep(i,N) for (int j = i+i; j < N; j += i) mu[j] -= mu[i];
    rep(i,N) for (int j = i; j < N; j += i) f[j].set(i);
    rep(i,N) for (int j = i; j < N; j += i) if (mu[j/i]) p[i].set(j);
    while (q--) {
        int op, x, y, z; cin >> op >> x >> y;
        if (op == 1) s[x] = f[y];
        else if (op == 2) cin >> z, s[x] = s[y]^s[z];
        else if (op == 3) cin >> z, s[x] = s[y]&s[z];
        else cout << ((s[x]&p[y]).count()&1);
    }
    return 0;
}