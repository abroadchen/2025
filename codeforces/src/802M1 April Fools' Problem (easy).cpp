//
// Created by Psy.C on 2026/9/19.
//

#include <bits/stdc++.h>
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
constexpr int N = 2210;
int n, k, a[N], ans;
int main() {
    n = rd(), k = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    sort(a+1, a+n+1);
    for (int i = 1; i <= k; ++i) ans += a[i];
    printf("%d\n", ans);
    return 0;
}