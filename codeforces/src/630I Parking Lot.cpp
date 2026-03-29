//
// Created by Psy.C on 2026/3/29.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll ksm(ll x, ll y) {
    ll t;
    for (t = 1; y; y>>=1, x=x*x)
        if (y&1) t*=x;
    return t;
}

ll n, ret, ans;
int main() {
    fast;
    cin >> n; n--;
    for (int i = 1; i < n+1; ++i) {
        ret = 0;
        if (i == 1) {
            ret = 4;
            if (i+1 <= n)
                ret *= 3*ksm(4, n-2);
        }
        else if (i == n) ret = 4ll*3*ksm(4, n-2);
        else ret = 4ll*3*3*ksm(4, n-3);
        ans += ret;
    }
    cout << ans << '\n';
    return 0;
}