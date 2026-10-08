//
// Created by Psy.C on 2026/10/8.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], ans;
int main() {
    fast;
    int n = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    for (int i = 2; i < n; ++i)
        if ((a[i]>a[i-1]&&a[i]>a[i+1])||(a[i]<a[i-1]&&a[i]<a[i+1]))
            ans++;
    cout << ans << '\n';
    return 0;
}