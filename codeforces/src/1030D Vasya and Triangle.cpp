//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
直角三角形面积需为 n*m/k。
因用整数坐标构造，要求 2nm 能被 k 整除（面积乘 2 后必须整除，否则无整数解）→ 不整除直接 NO
c = n/g、l = 2*m/j，初步给出两直角边候选 (c, l)。
若 l > m（超出矩形高度限制），则把 l 减半、c 加倍，使两直角边仍保持面积
n
m
/
k
nm/k 且不超界
输出直角顶点 (0,0) 和另两点 (0, l)、(c, 0)——即一个两直角边长度分别为 l、c 的直角三角形，面积恰为 l*c/2 = nm/k
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, k;
signed main() {
    fast;
    n = rd(), m = rd(), k = rd();
    if (n*m*2%k != 0) { cout << "NO\n"; return 0; }
    int g = __gcd(n,k), j = k/g, l = 2*m/j, c = n/g;
    if (l > m) { l /= 2; c *= 2; }
    cout << "YES\n";
    cout << "0 0\n";
    cout << "0 " << l << '\n';
    cout << c << " 0\n";
    return 0;
}