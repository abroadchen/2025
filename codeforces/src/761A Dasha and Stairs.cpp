//
// Created by Psy.C on 2026/9/5.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b; cin >> a >> b;
    if (a == 0 && b == 0) { cout << "NO\n"; return 0; }
    if (a == b || b - a == 1 || a - b == 1) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}