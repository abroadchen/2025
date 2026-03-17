//
// Created by Psy.C on 2026/3/17.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, t;
int main() {
    fast;
    cin >> n >> t;
    if (t < 10)
        for (int i = 0; i < n; ++i) cout << t;
    else {
        if (n == 1) cout << -1;
        else {
            cout << 1;
            for (int i = 1; i < n; ++i) cout << 0;
        }
    }
    cout << '\n';
    return 0;
}