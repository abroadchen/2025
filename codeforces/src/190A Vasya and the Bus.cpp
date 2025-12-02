//
// Created by Psy.C on 2025/12/2.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int mx; if (m >= n) mx = m; else mx = n;
    if (m == 0) cout << n << ' ' << n;
    else if (n == 0) cout << "Impossible";
    else cout << mx << ' ' << m + n - 1;
    return 0;
}