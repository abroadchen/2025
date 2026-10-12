//
// Created by Psy.C on 2026/10/12.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b, x, y, z;
int main() {
    fast;
    cin >> a >> b >> x >> y >> z;
    ll a1 = 2ll*x+y-a>0 ? 2ll*x+y-a : 0, a2 = 3ll*z+y-b>0 ? 3ll*z+y-b : 0;
    cout << a1 + a2 << '\n';
    return 0;
}