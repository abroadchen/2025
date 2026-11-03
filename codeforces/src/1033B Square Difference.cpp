//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
n < 2：0 和 1 不是素数，返回 false；
从 2 到 √n 依次试除，若存在因子返回 false（非素数）；
否则返回 true（素数）
条件一：a - b == 1，即 a = b + 1（a 比 b 大 1）；
条件二：check(a+b)，即 a + b 是素数。
两者都满足输出 YES，否则输出 NO
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

inline bool check(int n) {
    if (n < 2) return false;
    for (int i = 2; i*i <= n; ++i)
        if (n%i == 0) return false;
    return true;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int t, a, b;
signed main() {
    fast;
    t = rd();
    while (t--) {
        a = rd(), b = rd();
        if (a-b == 1 && check(a+b)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}