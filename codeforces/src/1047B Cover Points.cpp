//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int n;
int main() {
    fast;
    cin >> n;
    ll ans = -1;
    for (int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        ans = max(ans, (ll)a+b);
    }
    cout << ans << '\n';
    return 0;
}