//
// Created by Psy.C on 2026/2/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k;
int main() {
    fast;
    cin >> n >> k;
    cout << (n*6-1)*k << '\n';
    for (int i = 1, x; i <= n; ++i) {
        x = i*6-5;
        cout << x*k << ' ' << (x+1)*k << ' ' << (x+2)*k
            << ' ' << (x+4)*k << '\n';
    }
    return 0;
}