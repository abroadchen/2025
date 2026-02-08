//
// Created by Psy.C on 2026/2/7.
//
///O((n + m) × log(范围)): 其中范围是mx - mn
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100040
#define inf 1000000000
#define ll long long
using namespace std;

ll n, m, a[N], b[N];
ll ok(const ll x) {//x的总成本
    ll ans = 0;
    for (ll i = 1; i <= n; ++i)
        if (x > a[i]) ans += x - a[i];//x对于a[i]太大时的惩罚
    for (ll i = 1; i <= m; ++i)
        if (x < b[i]) ans += b[i] - x;//x对于b[i]太小时的惩罚
    return ans;
}


int main() {
    fast;
    cin >> n >> m;
    ll i, mn = inf, mx = 0;
    for (i = 1; i <= n; ++i) cin >> a[i], mn = min(mn, a[i]);
    for (i = 1; i <= m; ++i) cin >> b[i], mx = max(mx, b[i]);
    if (mn >= mx) { cout << "0\n"; return 0; }
    ll ans = inf, l = mn, r = mx;
    ans = min(ok(l), ok(r));
    while (l < r) {
        const ll m1 = (l+r)>>1, m2 = (m1+r)>>1, t1 = ok(m1), t2 = ok(m2);
        if (t1 > t2) l = m1; else r = m2;
        ans = min(ans, min(t1, t2));
    }
    cout << ans << '\n';
    return 0;
}