//
// Created by Psy.C on 2026/4/11.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int mod = 1e9+7;

int ksm(int a, int b) {
    int ans = 1;
    for (; b; b>>=1, a=a*1ll*a%mod)
        if (b&1) ans=ans*1ll*a%mod;
    return ans;
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    int ans;
    if (m == 1) ans = n + 1;
    else ans = (ksm(m, n) + m*1ll*(ksm(2*m-1,n)-ksm(m,n))%mod*
        ksm(m-1,mod-2)%mod)%mod;
    cout << ans << '\n';
    return 0;
}