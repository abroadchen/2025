//
// Created by Psy.C on 2026/9/20.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool check(int n) {
    for (int i = 1; i <= n; ++i)
        if (n%i == 0) return true;
    return false;
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    if (!check(n) && m-n == 1 || m == n) {
        cout << n; return 0;
    }
    cout << "2";
    return 0;
}