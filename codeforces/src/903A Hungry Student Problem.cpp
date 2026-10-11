//
// Created by Psy.C on 2026/10/11.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool ok(int t) {
    for (int i = 0; 7*i <= t; ++i)
        if ((t-7*i)%3 == 0) return true;
    return false;
}


int main() {
    fast;
    int n; cin >> n;
    while (n--) {
        int t; cin >> t;
        cout << (ok(t) ? "YES" : "NO") << '\n';
    }
    return 0;
}