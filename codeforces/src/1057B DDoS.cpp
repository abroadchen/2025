//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
n：数据个数；
a[N]：存每个数；
sum[N]：前缀和，sum[i] = 前 i 个数的累加和；
ans：答案（存在的最长连续子段长度）
双重循环枚举所有子区间 [i, j]（i≤j 起点终点组合）：
区间长度 len = j - i + 1；
区间和 = sum[j] - sum[i-1]（前缀和前缀差）；
判断条件：100 * (j-i+1) < sum[j] - sum[i-1]，即 100 × 区间长度 < 区间和（等价于区间平均值 > 100）。
若满足条件，用 ans = max(ans, j-i+1) 更新答案为该区间长度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 5e3+5;


inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, a[N], sum[N], ans;
int main() {
    fast;
    n = rd();
    rep(i,n) a[i] = rd(), sum[i] = sum[i-1] + a[i];
    rep(i,n) rep(j,n) if (100*(j-i+1) < sum[j] - sum[i-1])
        ans = max(ans, j-i+1);
    write(ans);
    return 0;
}