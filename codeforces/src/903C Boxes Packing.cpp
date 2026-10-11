//
// Created by Psy.C on 2026/10/11.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e3+5;
ll a, b[N], mx(1);
map<ll, ll> mp;
int main() {
    fast;
    cin >> a;
    for (int i = 1; i <= a; ++i) {
        cin >> b[i];
        mx = max(mx, ++mp[b[i]]);
    }
    cout << mx;
    return 0;
}