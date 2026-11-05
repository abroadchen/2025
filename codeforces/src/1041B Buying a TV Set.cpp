//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int a, b, c, d;
signed main() {
    fast;
    cin >> a >> b >> c >> d;
    int g = __gcd(c, d); c/=g; d/=g;
    cout << min(a/c, b/d);
    return 0;
}