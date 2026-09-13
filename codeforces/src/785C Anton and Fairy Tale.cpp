//
// Created by Psy.C on 2026/9/13.
//
/**
mid(mid+1)/2 + m*mid… 拆一下：
mid²+mid = 2·(mid(mid+1)/2)，即 mid² + mid = 2·[1+2+...+mid]。

所以不等式：2(1+2+...+mid) + 2m ≥ 2n
即：(1+2+...+mid) + m ≥ n

即：前 mid 项自然数和 + m ≥ n

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m;
int main() {
    fast;
    cin >> n >> m;
    if (m >= n) cout << n << '\n';
    else {
        ll l = 1, r = 1e10, mid, ans = 0;
        while (l <= r) {
            mid = (l+r)>>1ll;
            if (mid*mid+mid-2ll*n+2ll*m < 0) l = mid+1;
            else ans = mid, r = mid-1;
        }
        cout << ans+m << '\n';
    }
    return 0;
}