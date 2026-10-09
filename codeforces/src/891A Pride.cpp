//
// Created by Psy.C on 2026/10/9.
//
/**
读入
n
n 个数。
p 统计数组中 1 的个数。
d 累乘整个数组的 gcd
若所有数的整体 gcd
≠
1

=1，那么任意操作（只产生 gcd）都无法得到 1，输出 -1
若数组中已经有 1：每个非 1 元素只需与相邻的 1 做一次操作变成 gcd(1, x)=1，一次搞定一个，所以答案是非 1 的个数
n
−
p
n−p
数组无 1，需要先通过若干次相邻操作在某处造出一个 1。
枚举所有区间
[
i
,
j
]
[i,j]，计算其连续 gcd，找到能造出 1 的最短区间长度 len。
造出一个 1 需要 len-1 次操作（把区间内
l
e
n
len 个数逐步 gcd 成一个 1），之后剩下
n
−
1
n−1 个非 1 元素各需 1 次操作，共 len-1 + n-1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e3+5, inf = 0x3f3f3f3f;

int a[N];
int main() {
    fast;
    int n; cin >> n;
    int p = 0, d = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] == 1) p++;
        d = __gcd(d, a[i]);
    }
    if (d != 1) cout << -1 << '\n';
    else {
        if (p) { cout << n-p << '\n'; return 0; }
        int len = inf;
        for (int i = 1; i <= n; ++i) {
            d = a[i];
            for (int j = i+1; j <= n; ++j) {
                d = __gcd(a[j], d);
                if (d == 1) { len = min(len, j-i+1); break; }
            }
        }
        cout << len-1+n-1 << '\n';
    }
    return 0;
}