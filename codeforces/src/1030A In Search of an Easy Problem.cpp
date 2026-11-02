//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int n; cin >> n;
    bool f = false;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (x == 1) f = true;
    }
    cout << (f ? "HARD" : "EASY") << '\n';
    return 0;
}