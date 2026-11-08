//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int a, b;
signed main() {
    fast;
    cin >> a >> b;
    cout << "YES\n";
    for (int i = a; i <= b; i += 2)
        cout << i << ' ' << i+1 << '\n';
    return 0;
}