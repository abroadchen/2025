//
// Created by Psy.C on 2025/12/2.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, k; cin >> n >> k;
    if (k <= (n + 1) / 2) cout << 1 + (k - 1) / 2 << '\n';
    else {
        k -= (n + 1) / 2;
        cout << 2 + (k - 1) / 2 << '\n';
    }
    return 0;
}