//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
a[N] 存数列，s 存最终答案
n>>1 = n/2，循环 i 从 1 到 n/2 首尾配对（a[1]+a[n], a[2]+a[n-1],
对每对的和取平方，累加到 s。
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;
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

constexpr int N = 3e5+5;
int sqr(int x) { return x*x; }

int a[N], s;
signed main() {
    int n = rd();
    rep(i,n) a[i] = rd();
    sort(a+1,a+n+1);
    rep(i,n>>1) s += sqr(a[i]+a[n+1-i]);
    write(s), putchar('\n');
    return 0;
}