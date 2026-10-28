//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (x%2 == 0) cout << x-1 << ' ';
        else cout << x << ' ';
    }
    return 0;
}