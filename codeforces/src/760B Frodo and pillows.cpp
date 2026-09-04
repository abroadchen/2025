//
// Created by Psy.C on 2026/9/4.
//
/**
区间 [x-n+1, x] 中 n 个连续整数的和（等差数列求和）
区间 [1, x] 的和
若 res 小于等于 m，则返回 true（说明当前 x 合法

左侧求和 (res1)
求 [x-k+1, x] 中 k 个数的和
求 [1, x] 的和
右侧求和 (res2)
因为 x 被重复统计了一次，所以要减去一次

将 m 减去 n，调整为剩余的资源量

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m;
bool f1(ll x) {
    ll res = 0;
    if (n < x) res = ((x-n+1)+x)*n/2; else res = (1+x)*x/2;
    return res <= m;
}

ll k;
bool f2(ll x) {
    ll res1, res2;
    if (k < x) res1 = ((x-k+1)+x)*k/2; else res1 = (1+x)*x/2;
    if (n-k+1 < x) res2 = ((x-(n-k+1)+1)+x)*(n-k+1)/2;
    else res2 = (1+x)*x/2;
    return res1 + res2 - x <= m;
}

int main() {
    fast;
    cin >> n >> m >> k;
    if (n == m) { cout << "1"; return 0; }
    m = m - n;
    ll l = 0, r = m, ans = 0, mid = (l+r)>>1;
    if (k == 1 || k == n) {
        k = 1;
        while (l <= r) {
            mid = (l+r)>>1;
            if (f1(mid)) { ans = mid; l = mid + 1; }
            else r = mid - 1;
        }
    } else {
        while (l <= r) {
            mid = (l+r)>>1;
            if (f2(mid)) { ans = mid; l = mid + 1; }
            else r = mid - 1;
        }
    }
    cout << ans + 1 << '\n';
    return 0;
}