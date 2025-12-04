//
// Created by Psy.C on 2025/12/3.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        if ((n + 1) % 4 == 0) cout << n + 1 << '\n';
        else if ((n + 1) % 2 == 0) cout << n * 2 + 1 << '\n';
        else cout << n * 4 + 1 << '\n';
    }
    return 0;
}