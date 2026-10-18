//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e5+5;

int n, m, a[N], b[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,1,n) cin >> a[i], a[i] += a[i-1];
    rep(i,1,m) cin >> b[i], b[i] += b[i-1];
    int j = 1, ans = 0;
    rep(i,1,n) {
        while (j <= m && a[i] > b[j]) j++;
        ans += a[i] == b[j] && j <= m;
    }
    cout << ans << '\n';
    return 0;
}