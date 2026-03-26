//
// Created by Psy.C on 2026/3/26.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int inf = 0x7fffffff;///2147483647
int n, t;
ll sum;
int main() {
    fast;
    cin >> n;
    int mn = inf;
    while (n--) {
        cin >> t; sum += t;
        if (t&1) mn = min(mn, t);
    }
    if (sum&1) cout << sum-mn << '\n';
    else cout << sum << '\n';
    return 0;
}