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

ll c1, c2, c3, c4;
int main() {
    fast;
    while (cin >> c1 >> c2 >> c3 >> c4) {
        if (c1 == c4) {
            if (c4 == 0 && c3 != 0) cout << 0 << '\n';
            else cout << 1 << '\n';
        } else cout << 0 << '\n';
    }
    return 0;
}