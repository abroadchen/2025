//
// Created by Psy.C on 2026/5/8.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    if (n == 1) cout << -1 << '\n';
    else cout << n + 1 << ' ' << n*(n+1) << ' ' << n << '\n';
    return 0;
}