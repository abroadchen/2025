//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int a, b, c, d;
int main() {
    fast;
    cin >> a >> b >> c >> d;
    ll ans = 4 + max(a,c)*2 + 2*(b+d);
    cout << ans << '\n';
    return 0;
}