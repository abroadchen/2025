//
// Created by Psy.C on 2026/9/7.
//
/**
n 堆的数量，ans 作为 Nim 异或和的累加器
循环 n 次，每次处理一堆。
s = rd();：读入这堆石子的数量 s
这是解一元二次方程 x(x+1)/2 = s，即求满足"前 x 个正整数和恰好 ≤ s 的最大 x"（三角数）。由 x² + x - 2s = 0，
求根公式得 x = (-1 + sqrt(1+8s))/2。
这是本题的特型变换：题目把一堆大小为 s 的"蛋糕/石子"分裂成若干份，等价于把 s 拆成若干个连续递增的自然数块，而每堆等价于 Nim 里的一堆大小为 x
（其中 x 是使 1+2+...+x ≤ s 的最大 x）。参考实现正是用 sqrt(1+8s) 来求出这个 x
把这一堆变换后的"石子数 x"异或进 ans。这就是 Nim 游戏的 SG 值异或——整个局面先手必败当且仅当所有堆的异或和为 0。
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

int n, ans;
signed main() {
    fast;
    n = rd(), ans = 0;
    for (int i = 1, s, x; i <= n; ++i) {
        s = rd();
        x = ((int)sqrt((double)(1+8*s))-1)/2;
        ans ^= x;
    }
    cout << (ans ? "NO" : "YES") << '\n';
    return 0;
}