//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
从最大下标 n 开始，每次取相邻两个 a[i]（较大）与 a[i-1]（较小），累加差值 a[i]-a[i-1]，然后 i -= 2 跳两步。
因为已排序，所以每一对里较大者是 a[i]、较小者是 a[i-1]。
效果：ans += a[n]-a[n-1] + a[n-2]-a[n-3] + ... + a[2]-a[1]。
也就是把数组从大到小两两相邻配对，每对的差相加。若题目要最大化差值总和，这种大配大、次大配次大的方式能取到较大差值（贪心）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 3e4+10;

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

int a[N];
int main() {
    fast;
    int n = rd(), ans = 0;
    for (int i = 1; i <= n; ++i) a[i] = rd();
    sort(a+1, a+n+1);
    for (int i = n; i >= 2; i -= 2) ans += a[i] - a[i-1];
    write(ans);
    return 0;
}