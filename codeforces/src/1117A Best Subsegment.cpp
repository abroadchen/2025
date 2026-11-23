//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5, inf = 1e8-1;
int n, a[N], s, ans;
int main() {
    fast;
    cin >> n;
    int mx = -inf;
    rep(i,n) { cin >> a[i]; mx = max(mx, a[i]); }
    rep(i,n) {
        if (a[i] == mx) s++; else s = 0;
        ans = max(ans, s);//不断刷新最大值区间长度
    }
    cout << ans;
    return 0;
}