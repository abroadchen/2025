//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 5010;

ll p[N], p2[N], ct, m, a[N], b[N];
ll solve(ll x) {
    memset(p, 0, sizeof(p)); memset(p2, 0, sizeof(p2));
    ct = LLONG_MIN;
    rep(i,m) if (i != x) p[a[i]-1]++, p[b[i]]--;
    rep(i,n) p[i] += p[i-1];
    rep(i,n) p2[i+1] = p2[i] + (p[i] == 1);
    rep(i,m) if (i != x) ct = max(ct, -(p2[b[i]]-p2[a[i]-1]));
    rep(i,n) ct += p[i] > 0;
    return ct;
}

ll n, ans;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) cin >> a[i] >> b[i];
    rep(i,m) ans = max(ans, solve(i));
    cout << ans;
    return 0;
}