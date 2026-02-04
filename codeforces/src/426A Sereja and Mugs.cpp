//
// Created by Psy.C on 2026/2/4.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define inf 1e9
using namespace std;


int main() {
    fast;
    int m, n; cin >> m >> n;
    int mx = -inf, sum = 0;
    for (int i = 0, a; i < m; ++i) {
        cin >> a;
        if (a > mx) mx = a;
        sum += a;
    }
    if (sum - mx <= n) cout << "YES\n"; else cout << "NO\n";
    return 0;
}