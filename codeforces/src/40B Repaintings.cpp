//
// Created by Psy.C on 2025/9/25.
//

#include <ios>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, m, k; cin >> n >> m >> k;
    ll res = (max(0ll, n - 2 * (k - 1)) * max(0ll, m - 2 * (k - 1)) + 1) / 2 -
        (max(0ll, n - 2 * k) * max(0ll, m - 2 * k) + 1) / 2;
    cout << res << endl;
    return 0;
}