//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        int a; cin >> a;
        if (a%7 == 0) cout << a/7 << '\n';
        else cout << a/7+1 << '\n';
    }
    return 0;
}