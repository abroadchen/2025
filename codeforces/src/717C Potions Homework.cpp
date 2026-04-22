//
// Created by Psy.C on 2026/4/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7, mod = 10007;
int n, a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
        ans = (ans + 1ll*a[i]*a[n-i+1]%mod)%mod;//将配对乘积累加到ans
    cout << ans << '\n';
    return 0;
}