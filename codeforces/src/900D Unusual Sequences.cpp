//
// Created by Psy.C on 2026/10/10.
//
/**
先判断 y 是否被 x 整除，不整除直接无解输出 0（因为乘积含 x 却整除不了）
用
O
(
y
)
O(
y
​
 ) 枚举 y 的所有正因子存入数组 a（已去重、含 1 和 y 自身），排序。cnt 为因子个数
ksm(2, y/a[i]-1)：把 y/a[i] 看成"划分成长度为任意、有序的正整数段"，每段间可断开或不断开，共
y
/
a
[
i
]
−
1
y/a[i]−1 个"缝"，故
2
y
/
a
[
i
]
−
1
2
y/a[i]−1
  种有序切分。这是以 a[i] 为一个"单位"的整数拆分形式数量。
容斥去重：对所有是 a[i] 倍数的更大因子 a[j]（a[j] % a[i] == 0），减去 f[j]——去掉那些实际对应更大因子的重复计数。即 f[i] 表示以 a[i] 作为严格基准时的净方案数
在因子数组 a 里用 lower_bound 找到 x 的位置，输出对应的 f[位置]。

注意：因为 y % x == 0 已保证 x 是 y 的因子，所以 x 一定在 a 中，lower_bound 定位到的即 a[i] == x 的位置，f[pos] 即"乘积恰为 x（对应原问题 x 这一基准）"的方案数

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int mod = 1e9+7, N = 2005;
int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

int x, y, a[N], cnt, f[N];
signed main() {
    fast;
    cin >> x >> y;
    if (y%x) return cout << 0, 0;
    for (int i = 1; i*i <= y; ++i)
        if (y%i == 0) {
            a[++cnt] = i;
            if (i*i != y) a[++cnt] = y/i;
        }
    sort(a+1, a+cnt+1);
    for (int i = cnt; i >= 1; --i) {
        f[i] = ksm(2, y/a[i]-1);
        for (int j = i+1; j <= cnt; ++j)
            if (a[j]%a[i] == 0)
                f[i] = (f[i] + mod - f[j]) % mod;
    }
    cout << f[lower_bound(a+1, a+1+cnt, x)-a] << '\n';
    return 0;
}