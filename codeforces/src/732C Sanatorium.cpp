//
// Created by Psy.C on 2026/4/26.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll x, y, z, mn, md, mx;
void get() {
    ll num[3]; num[0] = x; num[1] = y; num[2] = z;
    sort(num, num+3);
    mn = num[0]; md = num[1]; mx = num[2];
}


int main() {
    fast;
    cin >> x >> y >> z; get();
    if (x == y && y == z) cout << 0 << '\n';
    else if (x >= y && y <= z) {
        if (mx == 1) cout << 0 << '\n';
        else if (x == z) cout << x - y - 1 << '\n';
        else cout << (mx-md-1)*2+md-mn << '\n';
    } else {
        if (mx == md) cout << md-mn-1 << '\n';
        else cout << (mx-md-1)*2+md-mn << '\n';
    }
    return 0;
}