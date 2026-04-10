//
// Created by Psy.C on 2026/4/8.
//

#include <bits/stdc++.h>
using namespace std;

inline int read() {
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

#define int long long
int n = read(), m = read(), k = read(), x[15], ans;
char ch;
signed main() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> ch;
            if (ch == 'Y') x[j]++;
        }
    for (int i = 1; i <= m; ++i)
        if (x[i] >= k) ans++;
    write(ans);
    return 0;
}