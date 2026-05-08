//
// Created by Psy.C on 2026/5/8.
//
///1378^n 的个位数字（最后一位）
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll ans = 1;
void dfs(ll x) {
    if (x == 0) return;
    dfs(x>>1);
    ans = ans*ans%10;
    if (x&1) ans = ans*1378%10;
}

ll n;
int main() {
    fast;
    cin >> n;
    if (n == 0) cout << "1\n";
    else {
        dfs(n);
        cout << ans << '\n';
    }
    return 0;
}